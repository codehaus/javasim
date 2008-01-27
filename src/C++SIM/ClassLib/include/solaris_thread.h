/*
 * Copyright (C) 1994-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: solaris_thread.h,v 1.4 1998/10/05 11:07:43 nmcl Exp $
 */

#ifndef SOLARIS_THREAD_H_
#define SOLARIS_THREAD_H_

#include <thread.h>
#include <synch.h>

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

class ostream;

/*
 * This is the Sun Solaris thread implementation of the Thread virtual class.
 */

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();

    static void* Execute (void*); // This routine calls the 'main' object code

    thread_t mid;
    sema_t sp;
    sema_t waitSem;
    Boolean dead;
};

class SolarisMutex : public Mutex
{
public:
    SolarisMutex ();
    ~SolarisMutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    mutex_t _theLock;
};

#endif
