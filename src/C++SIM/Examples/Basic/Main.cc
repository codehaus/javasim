/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <iostream.h>
#include <string.h>


#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef MACHINESHOP_H_
#  include "MachineShop.h"
#endif


int main (int argc, char** argv)
{
    Boolean isBreaks = FALSE;
    
    for (int i = 0; i < argc; i++)
    {
	if (::strcmp(argv[i], "-help") == 0)
	{
	    cout << "Usage: Main -breaks -help" << endl;
	    return 0;
	}
	if (::strcmp(argv[i], "-breaks") == 0)
	    isBreaks = TRUE;
    }

    Thread::Initialize(); // Initialize the threads package.

    /*
     * We don't need to call Resource::ref on m as it is created on
     * the stack. However, it would not cause any problems to do so,
     * and if objects are passed by pointer we may not know that one
     * has not been created on the heap. So, whenever we have a pointer
     * we will always call ref and unref before use.
     */

    MachineShop m(isBreaks); // Start up the real main body of the simulation.

    m.Await();               // Suspend main's thread (NOTE: this MUST be done
                             // by all applications.)

    m.Exit();                // Reactivate main thread and then exit
    
    return 0;
}
