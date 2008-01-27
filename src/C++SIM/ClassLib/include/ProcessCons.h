/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: ProcessCons.h,v 1.3 1996/12/09 10:09:56 nmcl Exp $
 */

#ifndef PROCESSCONS_H_
#define PROCESSCONS_H_

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

class ProcessCons
{
public:
    ProcessCons (Process &p, ProcessCons *n);
    ~ProcessCons ();
    
    Process     *car ();
    ProcessCons *cdr ();
    void SetfCdr (ProcessCons *n);

private:
    Process *Proc;
    ProcessCons *Next;
};


#include "ProcessCons.n"

#endif
