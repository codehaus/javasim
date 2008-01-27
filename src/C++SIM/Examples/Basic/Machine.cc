/*
 * Copyright (C) 1994-1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Machine.cc,v 1.4 1998/08/28 14:19:48 nmcl Exp $
 */

#ifndef MEAN_H_
#  include <Stat/Mean.h>
#endif

#ifndef MACHINE_H_
#  include "Machine.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#include <iostream.h>

extern Mean meanJobs;
extern long ProcessedJobs;
extern double MachineActiveTime;
extern Queue JobQ;

Machine::Machine (double mean)
                 : STime(new ExponentialStream(mean)),
                   operational(TRUE),
                   working(FALSE),
		   J(0)
{
}

Machine::~Machine ()
{
    delete STime;
    if (J)
	delete J;
}

void Machine::Body ()
{
    static int n = 0;
    
    double ActiveStart, ActiveEnd;

    for (;;)
    {
	working = TRUE;

	while (!JobQ.IsEmpty())
	{
	    ActiveStart = CurrentTime();

	    meanJobs += JobQ.QueueSize();

	    J = JobQ.Dequeue();

	    double serviceTime = ServiceTime();

	    Hold(serviceTime);
	    
	    ActiveEnd = CurrentTime();
	    MachineActiveTime += ActiveEnd - ActiveStart;
	    ProcessedJobs++;
	    delete J;
	    J = 0;
	}

	working = FALSE;
	Cancel();
    }
}

Boolean Machine::Processing () { return working; }

void Machine::Broken () { operational = FALSE; }

void Machine::Fixed () { operational = TRUE; }

Boolean Machine::IsOperational () { return operational; }

double Machine::ServiceTime () { return (*STime)(); }
