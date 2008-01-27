/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: ListBase.h,v 1.2 1996/12/09 10:09:56 nmcl Exp $  
 */

#ifndef LISTBASE_H_
#define LISTBASE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif


class ostream;


// All scheduler queue implementations should be derived from this

class ListBase
{
public:
    virtual void Insert (Process&, Boolean) = 0;
    virtual Boolean InsertBefore (Process&, Process&) = 0;
    virtual Boolean InsertAfter (Process&, Process&) = 0;
    virtual Process *Remove (const Process*) = 0;
    virtual const Process* getNext (const Process*) const = 0;

    virtual ostream& print (ostream&) const = 0;

protected:
    ListBase () {};
    virtual ~ListBase () {};
};

#endif
