/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: TerminateTest.cc,v 1.2 1996/04/09 10:53:04 nmcl Exp $
 */

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef TESTER_H_
#  include "Tester.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <iostream.h>


int main (int, char**)
{
    Thread::Initialize();
   
    Tester t;

    t.Await();
    t.Exit();
    
    return 0;
}
