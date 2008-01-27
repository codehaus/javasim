/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef DUMMYPROCESS_H_
#define DUMMYPROCESS_H_

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

class DummyProcess : public Process
{
public:
    DummyProcess ();
    ~DummyProcess ();

    void Body ();

    DummyProcess* next;
};

#endif
