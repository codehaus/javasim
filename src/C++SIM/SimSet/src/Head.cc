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

#include <iostream.h>

#ifndef HEAD_H_
#  include <SimSet/Head.h>
#endif

#ifndef LINK_H_
#  include <SimSet/Link.h>
#endif


Head::Head ()
            : first(0),
	      last(0)
{
}

Head::~Head () { Clear(); }

Link* Head::Suc () const
{
    return first;
}

Link* Head::Pred () const
{
    return last;
}

void Head::AddFirst (Link* element)
{
    if (!element)
	return;
    
    if (!first)
    {
	if (element->inList())
	    element->Out();
	
	first = element;
	last = element;
	element->theList = this;
    }
    else
    {
	element->Precede(first);
	first = element;
    }
}

void Head::AddLast (Link* element)
{
    if (!element)
	return;

    if (last)
    {
	element->Follow(last);
	last = element;
    }
    else
    {
	if (element->inList())
	    element->Out();
	
	first = element;
	last = element;
	element->theList = this;
    }
}

long Head::Cardinal () const 
{
    long numberOfElements = 0;
    Link *tempPtr = first;
    
    while (tempPtr)
    {
	numberOfElements++;
	tempPtr = tempPtr->Suc();
    }
    
    return numberOfElements;
}

void Head::Clear ()
{
    Link *tempPtr = first, *marker = 0;
    
    while (tempPtr)
    {
	marker = tempPtr;
	tempPtr = tempPtr->Suc();
	delete marker;
    }

    first = last = 0;
}


#ifdef NO_INLINES
#  define HEAD_CC_
#  include <SimSet/Head.n>
#  undef HEAD_CC_
#endif

