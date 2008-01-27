/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Producer.h,v 1.1 1996/12/09 10:10:09 nmcl Exp $
 */

#ifndef PRODUCER_H_
#define PRODUCER_H_

#ifndef ENTITY_H_
#  include <Event/Entity.h>
#endif

#ifndef RANDOM_H_
#  include <ClassLib/Random.h>
#endif

#ifndef SEMAPHORE_H_
#  include <Event/Semaphore.h>
#endif

/* Controls the rate at which Jobs arrive at the Machine */

class Producer : public Entity
{
public:
    Producer (double);
    virtual ~Producer ();

    virtual void Body ();

    static Semaphore _semaphore;
    
private:
    ExponentialStream* InterArrivalTime;
};

#endif
