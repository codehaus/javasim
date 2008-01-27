/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef SIGNALLER_H_
#define SIGNALLER_H_


#ifndef ENTITY_H_
#  include <Event/Entity.h>
#endif

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif


class Signaller : public Entity
{
public:
    Signaller (double);
    ~Signaller ();

    void Body ();

private:
    ExponentialStream* sTime;
};

#endif
