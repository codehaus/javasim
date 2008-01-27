/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef PROCESSITERATOR_H_
#define PROCESSITERATOR_H_

#ifndef PROCESSCONS_H_
#  include "ProcessCons.h"
#endif

class ProcessList;


class ProcessIterator
{
public:
    ProcessIterator (const ProcessList &L);
    Process *operator ()();

private:
    ProcessCons *ptr;
};

#endif
