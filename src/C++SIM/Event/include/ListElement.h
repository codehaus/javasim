/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: ListElement.h,v 1.1 1996/12/09 10:09:59 nmcl Exp $  
 */

#ifndef LISTELEMENT_H_
#define LISTELEMENT_H_

class Entity;

class ListElement
{
    friend class EntityList;

public:
    ListElement (Entity*);
    ~ListElement ();

private:
    Entity* _element;
    ListElement* _next;
};

#endif
