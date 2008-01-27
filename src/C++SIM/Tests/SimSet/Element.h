/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


/*
 * This is used to simply test the operation of the Head and Link classes.
 */


#ifndef ELEMENT_H_
#define ELEMENT_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef LINK_H_
#  include <SimSet/Link.h>
#endif


class Set;


class Element : public Link
{
public:
    Element ();
    Element (long);
    ~Element ();
    
    Boolean Belongs (Set*) const;

    long GetValue () const;
    void SetValue (long);
    
private:
    long value;
};


#include "Element.n"

#endif
