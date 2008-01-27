/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef SIGNALLER_H_
#  include "Signaller.h"
#endif

#ifndef PROCESSOR_H_
#  include "Processor.h"
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif


extern Processor* cpu;


Signaller::Signaller (double mean)
                                 : sTime(new ExponentialStream(mean))
{
}

Signaller::~Signaller ()
{
    if (sTime)
        delete sTime;
}

void Signaller::Body ()
{
    for (;;)
    {
        Hold((*sTime)());
	Job* j = new Job(TRUE);
	Interrupt(*cpu, FALSE);
    }
}
