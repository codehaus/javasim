/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <iostream.h>

#ifndef RESOURCE_H_
#  include <Common/Resource.h>
#endif

#ifndef MACHINESHOP_H_
#  include "MachineShop.h"
#endif

#ifndef PROCESSOR_H_
#  include "Processor.h"
#endif

#ifndef SIGNALLER_H_
#  include "Signaller.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#ifndef ARRIVALS_H_
#  include "Arrivals.h"
#endif

Processor* cpu;
Queue JobQ;
Queue SignalQ;
long ProcessedJobs = 0;
long SignalledJobs = 0;
double TotalResponseTime = 0;
double MachineActiveTime = 0;


MachineShop::MachineShop () {}

MachineShop::~MachineShop () {}

void MachineShop::Body ()
{
    Signaller* s = new Signaller(1000);
    Arrivals* A = new Arrivals(2);
    cpu = new Processor(10);
    Job* J = new Job(FALSE);

#ifndef NO_RESOURCE
    Resource::ref(s);
    Resource::ref(A);
    Resource::ref(cpu);
#endif

    cpu->Activate();
    A->Activate();
    s->Activate();

    Scheduler::scheduler().Resume();

    WaitFor(*cpu);

    cout << "Total jobs processed " << ProcessedJobs << endl;
    cout << "Total signals processed " << SignalledJobs << endl;

    Scheduler::scheduler().reset();    
    Scheduler::scheduler().Suspend();

    cpu->terminate();
    A->terminate();
    s->terminate();

    /*
     * Must reactivate main thread before this thread "dies" or there
     * will be nothing waiting to "catch" us.
     */

#ifndef NO_RESOURCE
    Resource::unref(cpu);
    Resource::unref(A);
    Resource::unref(s);
#else
    if (cpu)
	delete cpu;
    if (A)
	delete A;
    if (s)
	delete s;
#endif

    Thread::mainResume();
}

void MachineShop::Await ()
{
    Resume();
    Thread::Self()->Suspend();
}

void MachineShop::Exit ()
{
    Thread::Exit();
}
