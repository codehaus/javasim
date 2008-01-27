/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: DummyProcess.h,v 1.1 1996/03/19 12:03:18 nmcl Exp $
 */

#ifndef DUMMYPROCESS_H_
#define DUMMYPROCESS_H_

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif

class DummyProcess : public Process
{
public:
    DummyProcess (double);
    ~DummyProcess ();

    void Body ();

    DummyProcess* next;
    
private:
    double        waitTime;
    UniformStream dataStream;
};

#endif
