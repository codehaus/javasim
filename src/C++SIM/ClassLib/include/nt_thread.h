/*
 * Copyright (C) 1994-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: nt_thread.h,v 1.4 1998/08/28 14:19:35 nmcl Exp $
 */

#ifndef NT_THREAD_H_
#define NT_THREAD_H_

#include <stdlib.h>
#include <sys/types.h>
#include <windows.h>
#include <process.h>

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

#ifndef thread_t
#define thread_t long
#endif

class ostream;

class ThreadData
{
public:
    ThreadData ();
    ~ThreadData ();

    // This routine calls the 'main' object code    
    static DWORD Execute (LPDWORD);

    int _prio;
    HANDLE sem;
    HANDLE thrHandle;
    unsigned long mid;
    Boolean dead;

    static Thread* mainThread;
};

class NT_Mutex : public Mutex
{
public:
    NT_Mutex ();
    ~NT_Mutex ();

    Boolean lock ();
    Boolean unlock ();

private:
    HANDLE _theLock;
};

#endif
