/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Tester.cc,v 1.3 1997/03/18 13:47:30 nmcl Exp $
 */

#include <iostream.h>

#ifndef RESOURCE_H_
#  include <Common/Resource.h>
#endif

#ifndef TESTER_H_
#  include "Tester.h"
#endif

#ifndef DUMMYPROCESS_H_
#  include "DummyProcess.h"
#endif

long numberOfJobs = 0;

Tester::Tester (long processes, long iter, int hold)
               : number(processes),
		 iterations(iter),
		 justHold(hold),
		 dataStream(0.1, 10000.0),
                 head(0)
{
    if(justHold) {
	for (int i = 0; i < number; i++)
	{
	    DummyProcess *dp = new DummyProcess(dataStream());
	    dp->next = head;
	    head = dp;
    
	    dp->ActivateAt(dataStream());
	}
    }
}

Tester::~Tester ()
{
    if (head)
	delete head;
}

void Tester::Body ()
{

    if(!justHold) {
	for (int i = 0; i < number; i++)
	{
	    DummyProcess *dp = new DummyProcess(dataStream());
	    dp->next = head;
	    head = dp;
    
	    dp->ActivateAt(dataStream());
	}
    }

    Scheduler::scheduler().Resume();

    while (numberOfJobs < iterations)
	Hold(10000);

    Scheduler::scheduler().Suspend();
    
    Thread::mainResume();
}

void Tester::Await ()
{
    Resume();
    Thread::Self()->Suspend();
}

void Tester::Exit ()
{
    Thread::Exit();
}

