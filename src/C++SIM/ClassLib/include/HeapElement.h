/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: HeapElement.h,v 1.5 1996/12/09 10:09:54 nmcl Exp $ 
 */

#ifndef HEAPELEMENT_H_
#define HEAPELEMENT_H_


#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef PROCESSLIST_H_
#  include "ProcessList.h"
#endif


/*
 * This is the heap scheduler queue described in the C++SIM paper.
 * We try to maintain the LISP-like interface from ProcessList.
 */

class HeapElement
{
public:
    HeapElement (Process&, HeapElement* = 0);
    ~HeapElement ();

    ProcessList *car () const;
    HeapElement *cdr () const;
    void SetfCdr (HeapElement*);

    long bucketName () const;
    void setBucketName (long);

private:
    ProcessList* proc;
    HeapElement* next;
    long rangeTime;  // use this to name the 'buckets'
};


#include "HeapElement.n"

#endif
