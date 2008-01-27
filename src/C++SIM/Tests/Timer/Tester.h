/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Tester.h,v 1.2 1997/03/18 13:47:30 nmcl Exp $
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
    Tester (long, long, int);
    ~Tester ();

    void Body ();

    void Await ();
    void Exit ();

private:
    long number, iterations;
    UniformStream dataStream;
    int justHold;

    DummyProcess*  head;
};

#endif
