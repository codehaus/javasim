/*
 * Copyright (C) 1994-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: lwp_thread.h,v 1.2 1998/08/28 14:19:35 nmcl Exp $
 */

#ifndef LWP_THREAD_H_
#define LWP_THREAD_H_

extern "C"
{
#include <lwp/lwp.h>
}

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

extern "C"
{
#include <lwp/stackdep.h>
}

class ostream;

/*
 * This is the Sun thread implementation of the Thread virtual class. It
 * provides an implementation for all of the pure virtual functions declared
 * in the Thread base class.
 *
 * Note: if any problems occur when using the Sun thread package, try
 * increasing the stack size and/or the number of stacks to create in
 * Initialize.
 */

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();
    
    // This routine calls the 'main' object code
   
    static void Execute (Thread*);
    
    stkalign_t* stack;

    thread_t mid;
};

class LWP_Mutex : public Mutex
{
public:
    LWP_Mutex ();
    ~LWP_Mutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    mon_t _theLock;
};

#endif
