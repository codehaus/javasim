/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef BREAKS_H_
#  include "Breaks.h"
#endif

#ifndef MACHINE_H_
#  include "Machine.h"
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif

#include <iostream.h>


extern Machine* M;
extern Queue JobQ;
extern double MachineFailedTime;


Breaks::Breaks ()
{
    RepairTime = new UniformStream(10, 100);
    OperativeTime = new UniformStream(200, 500);
    interrupted_service = FALSE;
}

Breaks::~Breaks ()
{
    delete RepairTime;
    delete OperativeTime;
}

void Breaks::Body ()
{
    for(;;)
    {
        double failedTime = (*RepairTime)();

	Hold((*OperativeTime)());

	M->Broken();
	M->Cancel();

	if(!JobQ.IsEmpty())
	    interrupted_service = TRUE;

	Hold(failedTime);

	MachineFailedTime += failedTime;
	M->Fixed();
	
	if (interrupted_service)
	    M->ActivateAt(M->ServiceTime() + CurrentTime());
	else
	    M->ActivateAt();

	interrupted_service = FALSE;
    }
}
