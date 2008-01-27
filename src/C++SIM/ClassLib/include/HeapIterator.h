/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: HeapIterator.h,v 1.6 1996/12/09 10:09:55 nmcl Exp $ 
 */

#ifndef HEAPITERATOR_H_
#define HEAPITERATOR_H_

class HeapElement;
class Process;
class ProcessList;

class HeapIterator
{
    friend class ProcessHeap;
public:
    HeapIterator (const class ProcessHeap &H);
    ~HeapIterator ();

    ProcessList* operator ()();

private:
    HeapElement* current () const;
    long bucketName () const;

    HeapElement* currp;
    HeapElement* nextp;
};

#include "HeapIterator.n"

#endif
