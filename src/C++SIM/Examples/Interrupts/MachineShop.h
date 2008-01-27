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

#ifndef ENTITY_H_
#  include <Event/Entity.h>
#endif


/*
 * This class starts up all of the main processes involved in the simulation.
 */

class MachineShop : public Entity
{
public:
    MachineShop ();
    ~MachineShop ();

    void Body ();

    void Await ();
    void Exit ();
};

#endif
