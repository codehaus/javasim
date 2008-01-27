/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: ProcessCons.cc,v 1.3 1996/12/09 10:09:57 nmcl Exp $ 
 */

#ifndef PROCESSCONS_H_
#  include "ProcessCons.h"
#endif

ProcessCons::ProcessCons (Process &p, ProcessCons *n) { Proc = &p; Next = n; }

ProcessCons::~ProcessCons () {}


#ifdef NO_INLINES
#  define PROCESSCONS_CC_
#  include "ProcessCons.n"
#  undef PROCESSCONS_CC_
#endif
