/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef DUMMYPROCESS_H_
#  include "DummyProcess.h"
#endif

DummyProcess::DummyProcess ()
                            : next(0)
{
}

DummyProcess::~DummyProcess () {}

void DummyProcess::Body () {}
