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

#ifndef TESTER_H_
#  include "Tester.h"
#endif

int main (int, char**)
{
    Thread::Initialize(); // Initialize the threads package.
    
    Tester t;   // Start up the real main body of the simulation.
    t.Await();  // Suspend main's thread (NOTE: this MUST be done by all applications.)

    t.Exit();   // Reactivate main thread and then exit
    
    return 0;
}




