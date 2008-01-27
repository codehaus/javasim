/*
 * Copyright (C) 1993-1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Resource.h,v 1.2 1998/08/28 14:19:54 nmcl Exp $
 */

#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <stddef.h>

#ifndef BOOLEAN_H_
#   include <Common/Boolean.h>
#endif


class Resource
{
public:
    static void    ref   (Resource* resource);
    static Boolean unref (Resource* resource);

    void* operator new    (size_t amount);
    void  operator delete (void* memPtr);

protected:
    Resource ();
    virtual ~Resource ();

private:
    unsigned int   _referenceCount;
    Boolean        heapAllocated;

    static Boolean newCalled;
};

#endif
