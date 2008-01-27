/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Tester.cc,v 1.3 1998/07/15 16:02:36 nmcl Exp $
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

const double waitTime = 10.0;  // any time will do

Tester::Tester ()
	       : state1(0),
		 state2(0)
{
}

Tester::~Tester ()
{
    /*
     * Do not delete state1 as that process should
     * delete itself.
     */
    
#ifndef NO_RESOURCE
    Resource::unref(state2);
#else
    if (state2)
	delete state2;
#endif
}

/*
 * Create three processes. Terminate one immediately. Let one of the
 * others terminate itself, while the other deletes itself.
 */

void Tester::Body ()
{
    cout << "\nCreating first process." << endl;
    state1 = new DummyProcess(TRUE);
    
#ifndef NO_RESOURCE
    Resource::ref(state1);
#endif

    cout << "Activating first process." << endl;
    state1->ActivateAt(waitTime);

    state2 = new DummyProcess(FALSE);

#ifndef NO_RESOURCE
    Resource::ref(state2);
#endif

    cout << "Activating second process." << endl;
    
    state2->ActivateAt(waitTime);

    cout << "\nCreating third process." << endl;
    
    DummyProcess* dp = new DummyProcess(FALSE);
    
#ifndef NO_RESOURCE
    Resource::ref(dp);
#endif

    cout << "Terminating second process." << endl;

    dp->ActivateAt(waitTime);

    dp->terminate();
    
#ifndef NO_RESOURCE
    Resource::unref(dp);
#endif    

    Scheduler::scheduler().Resume();
    
    cout << "\nTester process holding." << endl;
    Hold(waitTime*2);

    cout << "\nSimulation terminating." << endl;
    
    Scheduler::scheduler().Suspend();
    Scheduler::scheduler().terminate();
	
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

