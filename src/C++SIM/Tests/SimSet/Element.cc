/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef ELEMENT_H_
#  include "Element.h"
#endif

#ifndef SET_H_
#  include "Set.h"
#endif


Element::Element ()
                  : value(0)
{
}

Element::Element (long x)
                        : value(x)
{
}

Element::~Element ()
{
}

Boolean Element::Belongs (Set* toCheck) const
{
    Boolean found = FALSE;
    Element* temp = (Element*) toCheck->First();
    
    while ((temp) && (!found))
    {
	if (temp->GetValue() == value)
	    found = TRUE;
	else
	    temp = (Element*) temp->Suc();
    }
    
    return found;
}


#ifdef NO_INLINES
#  define ELEMENT_CC_
#  include "Element.n"
#  undef ELEMENT_CC_
#endif
