/*
 * Copyright (C) 1994, 1995, 1996, 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Main.cc,v 1.2 1998/09/30 08:07:18 nmcl Exp $
 */

#include <iostream.h>
#include <string.h>

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef CONTROLLER_H_
#  include "Controller.h"
#endif


int main (int, char**)
{
    Thread::Initialize(); // Initialize the threads package.

    /*
     * We don't need to call Resource::ref on m as it is created on
     * the stack. However, it would not cause any problems to do so,
     * and if objects are passed by pointer we may not know that one
     * has not been created on the heap. So, whenever we have a pointer
     * we will always call ref and unref before use.
     */

    Controller c; // Start up the real main body of the simulation.

    c.Await();               // Suspend main's thread (NOTE: this MUST be done
                             // by all applications.)

    c.Exit();                // Reactivate main thread and then exit
    
    return 0;
}
