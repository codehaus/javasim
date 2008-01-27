/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

/*
 * This is used to simply test the operation of the Head and Link classes.
 */

#ifndef SET_H_
#define SET_H_

#ifndef HEAD_H_
#  include <SimSet/Head.h>
#endif

#ifndef LINK_H_
#  include <SimSet/Link.h>
#endif


class Set : public Head
{
public:
    Set ();
    ~Set ();
    
    Set* Intersect (Set*) const;
};

#endif