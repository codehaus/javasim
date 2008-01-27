/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef PROCESSLIST_H_
#define PROCESSLIST_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef PROCESSCONS_H_
#  include "ProcessCons.h"
#endif

#ifndef LISTBASE_H_
#  include "ListBase.h"
#endif

class ProcessIterator;

class ProcessList : public ListBase
{
    friend ProcessIterator;
    
public:
    ProcessList ();
    ~ProcessList ();

    void Insert (Process &, Boolean prior = FALSE);
    Boolean InsertBefore (Process &ToInsert, Process &Before);
    Boolean InsertAfter (Process &ToInsert, Process &After);
    Process *Remove (const Process *p=0);
    const Process* getNext (const Process*) const;

    ProcessCons* operator[] (int);

    ostream& print (ostream&) const;

private:
    ProcessCons *Head;
};

extern ostream& operator<< (ostream& strm, const ProcessList& pl);

#endif
