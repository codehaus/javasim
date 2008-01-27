/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


/*
 * This class essentially defines the linked list manager used by the SIMSET
 * class in SIMULA.
 */


#ifndef HEAD_H_
#define HEAD_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef LINKAGE_H_
#  include <SimSet/Linkage.h>
#endif

class Link;


class Head : public Linkage
{
    friend Link;
    
public:
    Head ();
    virtual ~Head ();

    virtual Link* Suc  () const;
    virtual Link* Pred () const;
    
    Link* First () const;
    Link* Last  () const;
    
    void AddFirst (Link*);
    void AddLast  (Link*);

    long Cardinal () const;
    Boolean Empty () const;

    void Clear ();
    
private:
    Link *first, *last;
};


#include <SimSet/Head.n>

#endif
