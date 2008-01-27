/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef HEAPITERATOR_H_
#  include "HeapIterator.h"
#endif

#ifndef HEAPELEMENT_H_
#  include "HeapElement.h"
#endif

#ifndef PROCESSHEAP_H_
#  include "ProcessHeap.h"
#endif

#ifndef PROCESSLIST_H_
#  include "ProcessList.h"
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif


/*
 * Assumes that we start at the root of the heap.
 */

HeapIterator::HeapIterator (const ProcessHeap &H)
                                                : currp(0),
                                                  nextp(H.Head)
{
}

HeapIterator::~HeapIterator () {}

ProcessList *HeapIterator::operator ()()
{
    if (nextp)
    {
        currp = nextp;
	nextp = nextp->cdr();
	return currp->car();
    }

    return (ProcessList*) 0;
}


#ifdef NO_INLINES
#  define HEAPITERATOR_CC_
#  include "HeapIterator.n"
#  undef HEAPITERATOR_CC_
#endif
