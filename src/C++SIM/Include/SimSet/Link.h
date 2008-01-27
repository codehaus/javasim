/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


/*
 * This class defines the elements of the linked lists within SIMSET.
 */


#ifndef LINK_H_
#define LINK_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef LINKAGE_H_
#  include <SimSet/Linkage.h>
#endif

class Head;


class Link : public Linkage
{
    friend Head;
    
public:
    virtual ~Link ();
    
    virtual Link* Suc () const;
    virtual Link* Pred () const;

    Link* Out ();
    void  InTo (Head* list);

    void Precede (Link* toPrecede);
    void Precede (Head* list);
    
    void Follow  (Link* toFollow);
    void Follow  (Head* list);

    Boolean inList () const;
    
protected:
    Link ();             // can only derive from this class
    
private:
    void RemoveElement ();

    void addAfter  (Link*);
    void addBefore (Link*);

    Link    *prev, *next;
    Head    *theList;
};


#include <SimSet/Link.n>

#endif
