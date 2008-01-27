/*
 * Copyright (C) 1994-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: cpp_task.h,v 1.2 1998/08/28 14:19:34 nmcl Exp $
 */

#ifndef CPP_TASK_H_
#define CPP_TASK_H_

#include <task.h>

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

class ostream;

/*
 * General notes: the C++ Task library does not have any notion of priorities,
 * and as such we need to simulate them (not too difficult).
 */

/*
 * A simple semaphore class based on the one in the Cfront 2.1 release notes.
 */

class _semaphore : public object
{
public:
    _semaphore ();
    ~_semaphore ();

    int pending ();
    void wait ();
    void signal ();

private:
    int sigs;	// the number of excess signals
};


/*
 * We do this because multiple (single) inheritence doesn't work
 * (setjmp/longjmp limitations).
 * Although multiple inheritence does, we should still support
 * older versions of C++, so ...
 */

class Basic_Task : public task
{
public:
    Basic_Task (Thread*, long, int = SIZE);
    virtual ~Basic_Task ();

    _semaphore sem;
};

/*
 * This is a threads interface to the C++ task library.
 */

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();
    
    Basic_Task* my_block;

    static long base_key;
    static task* _mainTask;
    static long mainTaskID;
};

class CPP_Mutex : public Mutex
{
public:
    CPP_Mutex ();
    ~CPP_Mutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    _semaphore _theLock;
};

#endif
