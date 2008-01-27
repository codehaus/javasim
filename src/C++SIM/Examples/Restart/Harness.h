/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef HARNESS_H_
#define HARNESS_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif


class Harness : public Process
{
public:
    Harness ();
    virtual ~Harness ();
    
    void Body();

    virtual void reset ();

    void doPassivate ();

private:
    Boolean status;
    Boolean _doPassivate;
};

#endif




