/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Queue.h,v 1.1 1996/12/09 10:10:10 nmcl Exp $
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef JOB_H_
#  include "Job.h"
#endif

/* This is the queue on which Jobs are placed before they are used. */

struct List
{
    Job* work;
    List* next;
};

class Queue
{
public:
    Queue ();
    ~Queue ();

    Boolean IsFull () const;
    Boolean IsEmpty () const;    
    
    Job* Dequeue ();
    void Enqueue (Job*);

private:
    List* head;
    long numberOfJobs;
};

#endif
