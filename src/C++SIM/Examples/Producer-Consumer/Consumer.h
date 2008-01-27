/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Consumer.h,v 1.1 1996/12/09 10:10:04 nmcl Exp $
 */

#ifndef CONSUMER_H_
#define CONSUMER_H_

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

class Consumer : public Entity
{
public:
    Consumer (double);
    virtual ~Consumer ();

    virtual void Body ();

    static Semaphore _semaphore;
    
private:
    ExponentialStream* InterArrivalTime;
};

#endif
