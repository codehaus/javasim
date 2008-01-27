/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: EntityList.h,v 1.2 1996/12/09 10:09:59 nmcl Exp $  
 */

#ifndef ENTITYLIST_H_
#define ENTITYLIST_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

class Entity;
class ListElement;

/*
 * FIFO queue.
 */

class EntityList
{
public:
    EntityList ();
    ~EntityList ();

    void add (Entity*);
    Entity* removeFirst ();
    Boolean remove (Entity*);

    Boolean find (Entity*) const;
    
    long numberOfElements () const;
    
private:
    ListElement* _headOfList;
    ListElement* _tailOfList;
    long _number;
};

#endif
