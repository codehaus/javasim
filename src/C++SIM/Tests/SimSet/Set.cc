/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef SET_H_
#  include "Set.h"
#endif

#ifndef ELEMENT_H_
#  include "Element.h"
#endif


Set::Set () {}

Set::~Set () {}

Set* Set::Intersect (Set* toCheck) const
{
    Set* tempSet = new Set;
    Element *E = 0;
    
    if (!Empty() && !toCheck->Empty())
    {
	E = (Element*) First();
	
	while (E)
	{
	    if (E->Belongs(toCheck))
	    {
		Element* toAdd = new Element(E->GetValue());
		toAdd->InTo(tempSet);
	    }
	    
	    E = (Element*) E->Suc();
	}
    }

    return tempSet;
}
