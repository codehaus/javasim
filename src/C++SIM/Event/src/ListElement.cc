/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: ListElement.cc,v 1.1 1996/12/09 10:10:01 nmcl Exp $ 
 */

#ifndef LISTELEMENT_H_
#  include <ListElement.h>
#endif

ListElement::ListElement (Entity* toAdd)
			 : _element(toAdd),
			   _next(0)
{
}

ListElement::~ListElement ()
{
}
