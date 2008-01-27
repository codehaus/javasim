/*
 * Copyright (C) 1991-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: thread.cc,v 1.15 1998/08/28 14:19:45 nmcl Exp $
 */

#include <iostream.h>

#if defined(DEBUG) && !defined(DEBUG_H_)
#  include <Common/Debug.h>
#endif

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

Thread* Thread::_head = (Thread*) 0; // Initialise head of Thread list
Boolean Thread::_initialized = FALSE;

void Thread::Insert (Thread* insertPosition, Thread* toInsert)
{
    if (insertPosition == (Thread*) 0)  // must be head of list
    {
	toInsert->next = _head;
	if (_head)
	    _head->prev = toInsert;
	_head = toInsert;
    }
    else
    {
	if (insertPosition->next)
	    insertPosition->next->prev = toInsert;
	toInsert->next = insertPosition->next;
	toInsert->prev = insertPosition;
	insertPosition->next = toInsert;
    }
}

void Thread::Remove (Thread* toRemove)
{
    if (toRemove->prev == (Thread*) 0)  // deal with head of list first
    {
	_head = toRemove->next;
	_head->prev = (Thread*) 0;
    }
    else
    {
	toRemove->prev->next = toRemove->next;
	if (toRemove->next)
	    toRemove->next->prev = toRemove->prev;
    }
}

long Thread::Identity () const { return thread_key; }

Thread* Thread::Self ()
{
    if (!_head) return (Thread*) 0;

    // Use any thread object (e.g., _head) to get access to the current thread

    long my_id = _head->Current_Thread();
    Thread* marker = (Thread*) 0;
    
    for (marker = _head; marker; marker = marker->next)
	if (marker->thread_key == my_id)
	    break;

    return marker;
}

// go through list and print out information on all threads

ostream& Thread::printAll (ostream& strm)
{
    strm << "\n";
    for (Thread* marker = _head; marker; marker = marker->next)
	strm << "Thread key: " << marker->thread_key << "\n";
    
    return strm;
}

ostream& operator<< (ostream& strm, const Thread& t)
{
    return t.print(strm);
}

/*
 * All the real work is done in the thread specific
 * class.
 */

Mutex::Mutex ()
{
}

Mutex::~Mutex ()
{
}
