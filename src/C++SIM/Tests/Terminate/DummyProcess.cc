/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <iostream.h>

#ifndef DUMMYPROCESS_H_
#  include "DummyProcess.h"
#endif

DummyProcess::DummyProcess (Boolean delSelf)
			   : deleteSelf(delSelf)
{
}

DummyProcess::~DummyProcess ()
{
    if (deleteSelf)
	cout << "Second process destructor called." << endl;
}

void DummyProcess::Body ()
{
    if (Process::current() != this)
	cerr << "Error with current process!" << endl;
    
    if (!deleteSelf)
    {
	cout << "\nThird process activated." << endl;
	cout << "Now self terminating." << endl;

	terminate();
    }
    else
    {
	cout << "\nSecond process activated." << endl;
	cout << "Now deleting self." << endl;
	
#ifndef NO_RESOURCE
	Resource::unref(this);
#else
	delete this;
#endif
    }
}
