/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#include <iostream.h>

#ifndef PROCESSOR_H_
#  include "Processor.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif


extern Queue JobQ;
extern Queue SignalQ;
extern long ProcessedJobs;
extern long SignalledJobs;


Processor::Processor (double mean)
                                 : sTime(new ExponentialStream(mean))
{
}

Processor::~Processor ()
{
    if (sTime)
        delete sTime;
}

void Processor::Body ()
{
    Job* j = (Job*) 0;

    for (;;)
    {
	if (Wait((*sTime)()))
	{
	    if (!JobQ.IsEmpty())
	    {
	        j = JobQ.Dequeue();
		delete j;
		ProcessedJobs++;
	    }
	}
	else
	{
	    if (SignalQ.IsEmpty())
	        cerr << "Error - signal caught, but no message given!" << endl;
	    else
	    {
	        j = SignalQ.Dequeue();
		delete j;
		SignalledJobs++;
	    }
	}

	if (SignalledJobs == 2)
	    terminate();
    }
}
