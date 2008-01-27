/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef JOB_H_
#define JOB_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif


/*
 * Instances of this class represent the jobs which the Machine attempts
 * to process.
 */

class Job
{
public:
    Job (Boolean);
    ~Job ();
};

#endif
