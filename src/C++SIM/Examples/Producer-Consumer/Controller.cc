/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Controller.cc,v 1.1 1996/12/09 10:10:04 nmcl Exp $
 */

#include <iostream.h>

#ifndef RESOURCE_H_
#  include <Common/Resource.h>
#endif

#ifndef CONTROLLER_H_
#  include "Controller.h"
#endif

#ifndef PRODUCER_H_
#  include "Producer.h"
#endif

#ifndef CONSUMER_H_
#  include "Consumer.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

long TotalNumberOfJobs = 0;
long NumberOfJobsConsumed = 0;
Queue JobQueue;

Controller::Controller ()
{
}

Controller::~Controller () {}

void Controller::Body ()
{
    Producer* p = new Producer(10);
    Consumer* c = new Consumer(10);
    
#ifndef NO_RESOURCE
    Resource::ref(p);
    Resource::ref(c);
#endif

    p->Activate();
    c->Activate();

    Scheduler::scheduler().Resume();

    Hold(10000);

    cout << "Total number of jobs present " << TotalNumberOfJobs << endl;
    cout << "Total number of jobs processed " << NumberOfJobsConsumed << endl;
    
    Scheduler::scheduler().reset();
    Scheduler::scheduler().Suspend();

    p->terminate();
    c->terminate();

#ifndef NO_RESOURCE
    Resource::unref(p);
    Resource::unref(c);
#else
    if (p)
	delete p;
    if (c)
	delete c;
#endif

    /*
     * Must reactivate main thread before this thread "dies" or there
     * will be nothing waiting to "catch" us.
     */
    
    Thread::mainResume();
}

void Controller::Await ()
{
    Resume();
    Thread::Self()->Suspend();
}

void Controller::Exit ()
{
    Thread::Exit();
}
