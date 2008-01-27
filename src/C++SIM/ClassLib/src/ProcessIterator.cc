/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef PROCESSITERATOR_H_
#  include "ProcessIterator.h"
#endif

#ifndef PROCESSLIST_H_
#  include "ProcessList.h"
#endif


ProcessIterator::ProcessIterator (const ProcessList &L) { ptr = L.Head; }

Process *ProcessIterator::operator ()()
{
    if (ptr)
    {
	ProcessCons *p = ptr;
	ptr = ptr->cdr();
	return p->car();
    }

    return (Process*) 0;
}
