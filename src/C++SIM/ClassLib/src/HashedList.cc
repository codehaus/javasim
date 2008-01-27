/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <iostream.h>

#ifndef THREAD_H_
#  include <ClassLib/thread.h>
#endif

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#if defined(DEBUG) && !defined(DEBUG_H_)
#  include <Common/Debug.h>
#endif

#ifndef HASHEDLIST_H_
#  include "HashedList.h"
#endif

#ifndef PROCESSITERATOR_H_
#  include "ProcessIterator.h"
#endif

HashedList::HashedList (int size)
                       : listSize(size),
			 numberOfEntries(0)
{
    hashedList = new ProcessList* [listSize];

    for (int i = 0; i < listSize; i++)
	hashedList[i] = new ProcessList;
}

HashedList::~HashedList ()
{
    for (int i = 0; i < listSize; i++)
	delete hashedList[i];

    delete [] hashedList;
}

// returns the next process to be activated after current

const Process* HashedList::getNext (const Process* current) const
{
    return findMinimum(current);
}

void HashedList::Insert (Process &ToInsert, Boolean prior)
{
#ifdef DEBUG
    debug_stream << FUNCTIONS << FAC_PROCESSLISTS << VIS_PUBLIC;
    debug_stream << "void HashedList::Insert ( " << ToInsert.evtime() << ", "
		 << ((prior) ? "TRUE" : "FALSE") << " )" << endl;
#endif    

    numberOfEntries++;
    hashedList[timeToKey(ToInsert.evtime())]->Insert(ToInsert, prior);
}

Boolean HashedList::InsertBefore (Process& ToInsert, Process& Before)
{
#ifdef DEBUG
    debug_stream << FUNCTIONS << FAC_PROCESSLISTS << VIS_PUBLIC;
    debug_stream << "Boolean HashedList::InsertBefore ( " << ToInsert.evtime() << ", "
		 << Before.evtime() << " )" << endl;
#endif

    numberOfEntries++;
    return hashedList[timeToKey(Before.evtime())]->InsertBefore(ToInsert, Before);
}

Boolean HashedList::InsertAfter (Process &ToInsert, Process &After)
{
#ifdef DEBUG
    debug_stream << FUNCTIONS << FAC_PROCESSLISTS << VIS_PUBLIC;
    debug_stream << "Boolean HashedList::InsertAfter ( " << ToInsert.evtime() << ", "
		 << After.evtime() << " )" << endl;
#endif

    numberOfEntries++;
    return hashedList[timeToKey(After.evtime())]->InsertAfter(ToInsert, After);
}

/*
 * Find process with minimum time after process in parameter
 * (NULL means next process to run).
 */

Process* HashedList::findMinimum (const Process* from) const
{
    Process* toReturn = 0;

    for (int i = 0; i < listSize; i++)
    {
	ProcessIterator iter(*hashedList[i]);
	Process *p = iter();

	if (p)
	{
	    if (p->evtime() == Process::Never)
	    {
		error_stream << FATAL << "HashedList::findMinimum found process with negative time!" << endl;
		Thread::Exit(-1);
	    }
	    
	    if (toReturn)
	    {
		if (p->evtime() == toReturn->evtime())
		{
		    do
		    {
			if (p == from)
			{
			    toReturn = iter();  // get next process in list
			    break;
			}
			else p = iter();
			
		    } while (p != 0);
		}
		else
		{
		    if (p->evtime() < toReturn->evtime())
			toReturn = p;
		}
	    }
	    else
		toReturn = p;
	}
    }

    return toReturn;
}

Process* HashedList::Remove (const Process *element)
{
    if (numberOfEntries == 0)
	return (Process*) 0;
    
    // Change unspecified element to "remove head of list" request
    
    if (element == (Process*) 0)
	return Remove(findMinimum());

    Process* toReturn = (Process*) 0;
    int key = timeToKey(element->evtime());

    numberOfEntries--;
    
    if (!(*hashedList[key])[0])  // not in queue, so active/passive
	return (Process*) 0;

    return hashedList[key]->Remove(element);
}

ostream& HashedList::print (ostream& strm) const
{
    for (int i = 0; i < listSize; i++)
    {
        strm << "\nList element " << i << "\n";
	strm << *hashedList[i];
    }

    return strm;
}

#ifdef NO_INLINES
#  define HASHEDLIST_CC_
#  include "HashedList.n"
#  undef HASHEDLIST_CC_
#endif