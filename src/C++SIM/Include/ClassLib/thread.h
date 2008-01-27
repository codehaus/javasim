/*
 * Copyright (C) 1991-1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: thread.h,v 1.14 1998/08/28 14:19:53 nmcl Exp $ 
 */

#ifndef THREAD_H_
#define THREAD_H_

#ifndef RESOURCE_H_
#  include <Common/Resource.h>
#endif

/*
 * Because not every thread package provides an easy way of identifying and
 * locating threads, the Thread class does provide such a scheme through the
 * use of the Identify and Self operations. A linked list of threads is formed
 * and added to whenever a new thread is created.
 */

class ostream;
class ThreadData;

class Thread : public Resource
{
    friend ThreadData;
    
public:
    virtual void Suspend (); // How to suspend a thread
    virtual void Resume ();  // How to resume a suspended thread
    
    virtual void Body () = 0;    // The 'main' part of the code

    // Should return some unique thread identity key
    
    virtual long Current_Thread () const;

    virtual long Identity () const; // Returns the identify of this thread

    static Thread* Self ();         // Returns the current thread

    // Exit program
    
    static void Exit (int = 0);

    // Need routine to explicitly resume main.
    
    static void mainResume ();
    
    // Initialize must be called exactly once at the start of the program
    
    static void Initialize ();
    
    virtual ostream& print (ostream&) const;
    static  ostream& printAll (ostream&);

protected:
    Thread (Boolean create = TRUE);
    Thread (unsigned long stackSize);
    virtual ~Thread ();

    virtual void terminateThread (); // terminate and release resources
    
    long thread_key;    // key which must be set in derived class.
    ThreadData* _data;

private:
    void Insert (Thread*, Thread*);
    void Remove (Thread*);
    
    Thread* next;
    Thread* prev;

    static Thread* _head;
    static Boolean _initialized;
};


class Mutex : public Resource
{
public:
    virtual Boolean lock () = 0;
    virtual Boolean unlock () = 0;

    static Mutex* create ();
    
protected:
    Mutex ();
    virtual ~Mutex ();
};
    
extern ostream& operator<< (ostream& strm, const Thread& t);

#endif
