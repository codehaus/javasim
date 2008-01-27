/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef MACHINESHOP_H_
#define MACHINESHOP_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif


/*
 * This class starts up all of the main processes involved in the simulation.
 * If the -DBREAKS option is added to the CFLAGS for the Makefile then the
 * Breaks process will be created to deactivate of the Machine process at
 * suitable intervals. Otherwise it will not be created and the Machine will
 * operate uninterrupted.
 */

class MachineShop : public Process
{
public:
    MachineShop (Boolean);
    ~MachineShop ();

    void Body ();

    void Await ();
    void Exit ();

private:
    Boolean useBreaks;
};

#endif
