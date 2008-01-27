/*
 * Copyright (C) 1993,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Resource.cc,v 1.1 1995/02/28 13:26:10 nmcl Exp $
 */

#include <iostream.h>

#ifndef RESOURCE_H_
#   include <Common/Resource.h>
#endif

Boolean Resource::newCalled = FALSE;


Resource::Resource ()
                   : _referenceCount(0),
                     heapAllocated(newCalled)
{
    Resource::newCalled = FALSE;
}

Resource::~Resource ()
{
    if ((_referenceCount != 0) && (heapAllocated))
        cerr << "Resource::~Resource : _referenceCount = "
	     << _referenceCount << endl;
}

/*
 * If allocated on the stack then we could simply ignore all
 * ref and unref requests. Currently we process them but
 * treat "error" conditions differently.
 */

void Resource::ref (Resource* resource)
{
    if (resource != NULL)
        resource->_referenceCount++;
}

Boolean Resource::unref (Resource* resource)
{
    if (resource != (Resource*) 0)
    {
        if (resource->_referenceCount > 0)
            resource->_referenceCount--;
        else
	    if (resource->heapAllocated)
	        cerr << "Resource::unref : _referenceCount == 0" << endl;

        if ((resource->_referenceCount == 0) && (resource->heapAllocated))
        {
            delete resource;
            resource = (Resource*) 0;
        }
    }

    if ((resource != (Resource*) 0) && (resource->heapAllocated))
        return FALSE;
    else
        return TRUE;
}

void* Resource::operator new (size_t amount)
{
    Resource::newCalled = TRUE;
    return ::new char[amount];
}

void Resource::operator delete (void* memPtr)
{
    ::delete [] memPtr;
}
