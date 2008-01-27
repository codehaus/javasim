/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef ARRIVALS_H_
#  include "Arrivals.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

Arrivals::Arrivals (double mean) { InterArrivalTime = new ExponentialStream(mean); }

Arrivals::~Arrivals () { delete InterArrivalTime; }

void Arrivals::Body ()
{
    for(;;)
    {
	Hold((*InterArrivalTime)());
	Job* work = new Job(FALSE);
    }
}
