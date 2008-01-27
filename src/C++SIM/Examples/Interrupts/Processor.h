/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef PROCESSOR_H_
#define PROCESSOR_H_

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif

#ifndef ENTITY_H_
#  include <Event/Entity.h>
#endif

#ifndef QUEUE_H_
#  include "Queue.h"
#endif


class Processor : public Entity
{
public:
    Processor (double);
    ~Processor ();

    void Body ();

private:
    ExponentialStream* sTime;
};

#endif

