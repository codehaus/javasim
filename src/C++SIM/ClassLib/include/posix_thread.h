/*
 * Copyright (C) 1994, 1995, 1996, 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: posix_thread.h,v 1.7 1998/10/05 12:03:51 nmcl Exp $
 */

#ifndef POSIX_THREAD_H_
#define POSIX_THREAD_H_

#include <pthread.h>
#include <semaphore.h>

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

class ostream;

#define any_t void*

/*
 * This is the Posix thread implementation of the Thread virtual class.
 */

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();
    
    // This routine calls the 'main' object code
    
    static void* Execute (void*);

    Boolean dead;
    pthread_t _thread;
#ifndef PTHREAD_DRAFT_SOLARIS
    pthread_mutex_t _lock;
#else
    sem_t waitSem;
    sem_t _lock;
#endif
    pthread_attr_t _attr;

    static long base_key;
};


class PosixMutex : public Mutex
{
public:
    PosixMutex ();
    ~PosixMutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    pthread_mutex_t _theLock;
};

#endif
