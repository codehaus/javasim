/*
 * Copyright (C) 1994, 1995, 1996, 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Semaphore.h,v 1.4 1998/09/30 08:07:25 nmcl Exp $ 
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef TRIGGERQUEUE_H_
#  include <Event/TriggerQueue.h>
#endif

class Entity;
class EntityList;

/*
 * Classic semaphores can "accumulate" more resources than the starting
 * value. The ceiling parameter is used to indicate whether or not the
 * resource count should ever go beyond the initial value - the default
 * is that it should.
 */

class Semaphore
{
public:
    enum Outcome { DONE, NOTDONE, WOULD_BLOCK };
	
    Semaphore ();
    Semaphore (long number, Boolean ceiling = FALSE); // number of resources available
    virtual ~Semaphore ();

    virtual Semaphore::Outcome Get (Entity*);
    virtual Semaphore::Outcome Release ();
    
    /*
     * Try to get the semaphore, but return if this would block
     * the caller.
     */
    
    virtual Semaphore::Outcome TryGet (Entity*);

    long NumberWaiting () const;

private:
    TriggerQueue waitingList;
    long numberWaiting;
    long numberOfResources;
    long currentResources;
    Boolean haveCeiling;
};

#endif
