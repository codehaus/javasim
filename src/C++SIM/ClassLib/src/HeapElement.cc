/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef HEAPELEMENT_H_
#  include "HeapElement.h"
#endif

#ifndef PROCESSLIST_H_
#  include "ProcessList.h"
#endif


HeapElement::HeapElement (Process& p, HeapElement* n)
                                                    : next(n),
						      rangeTime(0)
{
    proc = new ProcessList;
    proc->Insert(p);
}

HeapElement::~HeapElement ()
{
    if (proc)
        delete proc;
}


#ifdef NO_INLINES
#  define HEAPELEMENT_CC_
#  include "HeapElement.n"
#  undef HEAPELEMENT_CC_
#endif
