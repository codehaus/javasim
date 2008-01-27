/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: TriggerQueue.h,v 1.3 1996/12/09 10:10:16 nmcl Exp $
 */

#ifndef TRIGGERQUEUE_H_
#define TRIGGERQUEUE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

class Entity;
class EntityList;
class Semaphore;

class TriggerQueue
{
    friend Entity;
    friend Semaphore;

public:
    TriggerQueue ();
    virtual ~TriggerQueue ();

    Boolean triggerAll ();
    Boolean triggerFirst (Boolean = TRUE);

protected:
    void insert (Entity*);
    Entity* remove ();

private:
    EntityList* head;
};

#endif
