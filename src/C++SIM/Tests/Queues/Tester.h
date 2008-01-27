/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef TESTER_H_
#define TESTER_H_

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif

class DummyProcess;

class Tester : public Process
{
public:
    enum StreamType { UNIFORM, NORMAL, EXPONENTIAL };

    Tester (long, StreamType);
    ~Tester ();

    void Body ();

    void Await ();
    void Exit ();

private:
    long number;
    double hi, lo;
    double mean, std;

    UniformStream*     us;
    NormalStream*      ns;
    ExponentialStream* es;
    StreamType         streamType;

    DummyProcess* head;
};

#endif
