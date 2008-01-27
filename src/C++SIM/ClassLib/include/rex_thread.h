/*
 * Copyright (C) 1991-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: rex_thread.h,v 1.2 1998/08/28 14:19:36 nmcl Exp $
 */

#ifndef REX_THREAD_H_
#define REX_THREAD_H_

#ifndef CONFIGURE_H_
#  include <Config/Configure.h>
#endif

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

class Thread;

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();

    struct sem* to_wait;
    struct pcb* my_block;

    static void Execute (int prio, char**, Thread* p1);
    
    static long base_key;
    static struct sem* mainThread;
    static long mainThreadID;
};


class RexMutex : public Mutex
{
public:
    RexMutex ();
    ~RexMutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    sem* _theLock;
};

#endif
