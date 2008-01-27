/*
 * Copyright (C) 1994-1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef MACHINE_H_
#  include "Machine.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#ifdef DEBUG
#  include <iostream.h>
#endif

extern Machine* M;
extern Queue JobQ;
extern long TotalJobs;
extern double TotalResponseTime;

Job::Job ()
{
    Boolean empty;

    ResponseTime = 0;
    ArrivalTime = Scheduler::scheduler().CurrentTime();
    empty = JobQ.IsEmpty();
    JobQ.Enqueue(this);
    TotalJobs++;

    if (empty && !M->Processing() && M->IsOperational())
	M->Activate();
}

Job::~Job ()
{
    ResponseTime = Scheduler::scheduler().CurrentTime() - ArrivalTime;

#ifdef DEBUG
    cout << "ArrivalTime is " << ArrivalTime << endl;
    cout << "Time now is " << Scheduler::scheduler().CurrentTime() << endl;
    cout << "ResponseTime is " << ResponseTime << endl;
#endif

    TotalResponseTime += ResponseTime;
}
