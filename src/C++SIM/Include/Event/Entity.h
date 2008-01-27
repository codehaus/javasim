/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Entity.h,v 1.8 1997/08/05 17:02:22 nmcl Exp $
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#if defined(DEBUG) && !defined(DEBUG_H_)
#  include <Common/Debug.h>
#endif

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

class TriggerQueue;
class Semaphore;

class Entity : public Process
{
    friend Semaphore;
    friend TriggerQueue;

public:
    virtual ~Entity ();

    // Interrupt process which in wait state.
    
    Boolean Interrupt (Entity&, Boolean = TRUE);
    void    trigger ();

    Boolean isWaiting () const;

    virtual void terminate ();       // terminate the process - no going back!

    /*
     * The pure virtual function, Body, defines the code that executes
     * in the process.
     */

    virtual void Body () = 0;

protected:
    Entity ();
    Entity (unsigned long stackSize);    

    Boolean Wait (double);                  // wait for set period of time
    Boolean WaitFor (Entity&, Boolean = FALSE);// wait for process to terminate
    Boolean WaitForTrigger (TriggerQueue&);
    void WaitForSemaphore (Semaphore&);

private:
    Entity* _isWaiting;  // process which will be resumed when this is terminated
    Boolean _interrupted;// was process interrupted?
    Boolean _triggered;  // was process triggered?
    Boolean _waiting;    // is this process waiting?
};

#include "Entity.n"

#endif
