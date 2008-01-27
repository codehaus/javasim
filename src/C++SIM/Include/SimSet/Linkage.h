/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


/*
 * This class defines the core element within SIMSET.
 */


#ifndef LINKAGE_H_
#define LINKAGE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

class Link;


class Linkage
{
public:
    virtual ~Linkage ();
    
    virtual Link* Suc () const = 0;
    virtual Link* Pred () const = 0;
    
protected:
    Linkage ();           // can only derive from this class
};

#endif
