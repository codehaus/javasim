/*
 * Copyright (C) 1994-1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Machine.h,v 1.3 1998/08/28 14:19:49 nmcl Exp $
 */

#ifndef MACHINE_H_
#define MACHINE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

class Job;


/*
 * This is the machine which services job requests. It is prone to simulated
 * failures caused by the Breaks process.
 */

class Machine : public Process
{
    friend class Breaks;

public:
    Machine (double);
    ~Machine ();

    void Body ();

    void Broken ();
    void Fixed ();
    Boolean IsOperational ();
    Boolean Processing ();
    double ServiceTime ();

private:
    ExponentialStream* STime;
    Boolean operational;
    Boolean working;
    Job* J;
};

#endif
