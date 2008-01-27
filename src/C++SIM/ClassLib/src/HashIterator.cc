/*
 * Copyright (C) 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: HashIterator.cc,v 1.1 1998/07/31 08:50:25 nmcl Exp $
 */

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef HASHEDLIST_H_
#  include "HashedList.h"
#endif

#ifndef HASHITERATOR_H_
#  include "HashIterator.h"
#endif

HashIterator::HashIterator (const HashedList& H)
			   : _list(&H),
			     _current(0)
{
}

HashIterator::~HashIterator ()
{
}

Process* HashIterator::operator ()()
{
    if (_list != 0)
	_current = _list->getNext(_current);
    else
	_current = 0;

    return _current;
}
