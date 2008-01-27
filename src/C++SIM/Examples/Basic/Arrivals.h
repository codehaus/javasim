/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef ARRIVALS_H_
#define ARRIVALS_H_

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif

class Job;


/* Controls the rate at which Jobs arrive at the Machine */

class Arrivals : public Process
{
public:
    Arrivals (double);
    virtual ~Arrivals ();

    virtual void Body ();

private:
    ExponentialStream* InterArrivalTime;
};

#endif
