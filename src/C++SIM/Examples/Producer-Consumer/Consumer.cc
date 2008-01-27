/*
 * Copyright (C) 1994, 1995, 1996, 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Consumer.cc,v 1.2 1998/09/30 08:07:17 nmcl Exp $
 */

#ifndef CONSUMER_H_
#  include "Consumer.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#ifndef PRODUCER_H_
#  include "Producer.h"
#endif

extern Queue JobQueue;
extern long NumberOfJobsConsumed;

Semaphore Consumer::_semaphore(0);

Consumer::Consumer (double mean)
		   : InterArrivalTime(new ExponentialStream(mean))
{
}

Consumer::~Consumer () { delete InterArrivalTime; }

void Consumer::Body ()
{
    for (;;)
    {
	if (JobQueue.IsEmpty())
	    Consumer::_semaphore.Get(this);

	Job* work = JobQueue.Dequeue();

	Producer::_semaphore.Release();
	NumberOfJobsConsumed++;
	
	Hold((*InterArrivalTime)());
    }
}
