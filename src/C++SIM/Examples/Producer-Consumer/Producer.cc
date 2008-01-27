/*
 * Copyright (C) 1994, 1995, 1996, 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Producer.cc,v 1.2 1998/09/30 08:07:24 nmcl Exp $
 */

#ifndef PRODUCER_H_
#  include "Producer.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#ifndef CONSUMER_H_
#  include "Consumer.h"
#endif

extern Queue JobQueue;
extern long TotalNumberOfJobs;

Semaphore Producer::_semaphore(0);

Producer::Producer (double mean)
		   : InterArrivalTime(new ExponentialStream(mean))
{
}

Producer::~Producer () { delete InterArrivalTime; }

void Producer::Body ()
{
    for (;;)
    {
	Job* work = new Job();

	if (JobQueue.IsFull())
	    Producer::_semaphore.Get(this);

	TotalNumberOfJobs++;
	JobQueue.Enqueue(work);
	Consumer::_semaphore.Release();
	
	Hold((*InterArrivalTime)());
    }
}
