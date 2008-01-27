#include <iostream.h>

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef TESTER_H_
#  include "Tester.h"
#endif

#ifndef HARNESS_H_
#  include "Harness.h"
#endif


const int iter = 4;


Tester::Tester ()
	       : dummy(0)
{
}

Tester::~Tester ()
{
#ifndef NO_RESOURCE
    Resource::unref(dummy);
#else    
    if (dummy)
	delete dummy;
#endif    
}

void Tester::Body ()
{
    dummy = new Harness;

#ifndef NO_RESOURCE
    Resource::ref(dummy);
#endif    

    for (int i = 0; i < iter; i++)
    {
	cout << "Iteration " << i << endl;

	Scheduler::scheduler().Resume();
	dummy->Activate();

	cout << "Tester holding." << endl;
	Hold(100);

	cout << "Tester woken." << endl;

	Scheduler::scheduler().reset();
    }

    dummy->doPassivate();
    dummy->Activate();
    Hold(100);
    
    cout << "End of simulation reached." << endl;

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
