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

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

class Harness;


class Tester : public Process
{
public:
    Tester ();
    virtual ~Tester ();
    
    void Body ();

    void Await ();
    void Exit ();

private:
    Harness* dummy;
};

#endif




