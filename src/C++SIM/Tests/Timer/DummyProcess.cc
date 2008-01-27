/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: DummyProcess.cc,v 1.1 1996/03/19 12:03:15 nmcl Exp $
 */

#ifndef DUMMYPROCESS_H_
#  include "DummyProcess.h"
#endif

extern long numberOfJobs;

DummyProcess::DummyProcess (double time)
			   : next(0),
			     waitTime(time),
			     dataStream(0.0, 500)
{
}

DummyProcess::~DummyProcess ()
{
    if (next)
	delete next;
}

void DummyProcess::Body ()
{
    for (;;)
    {
	Hold(dataStream());
	numberOfJobs++;
    }
}

