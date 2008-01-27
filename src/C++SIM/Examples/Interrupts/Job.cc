/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif


extern Scheduler* sc;
extern Queue JobQ;
extern Queue SignalQ;


Job::Job (Boolean isSignal)
{
    if (isSignal)
        SignalQ.Enqueue(this);
    else
        JobQ.Enqueue(this);
}

Job::~Job () {}
