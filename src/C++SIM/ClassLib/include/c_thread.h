/*
 * Copyright (C) 1994-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: c_thread.h,v 1.2 1998/08/28 14:19:33 nmcl Exp $
 */

#ifndef C_THREAD_H_
#define C_THREAD_H_

extern "C"
{
#include <cthread.h>
}

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

class Thread;

/*
 * General notes: the C Threads library does not have any notion of priorities.
 */

/*
 * This is a threads interface to the C threads library.
 */

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();
    
    cthread_t cid;
    mutex_t   mx;
    Boolean   dead;

    static void* Execute (void* p1);
    
    static long base_key;
    static Thread* mainThread;
    static long mainThreadID;
};

class C_Mutex : public Mutex
{
public:
    C_Mutex ();
    ~C_Mutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    mutex_t _theLock;
};

#endif
