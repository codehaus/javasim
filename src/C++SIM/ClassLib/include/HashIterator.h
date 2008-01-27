/*
 * Copyright (C) 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: HashIterator.h,v 1.1 1998/07/31 08:50:23 nmcl Exp $
 */

#ifndef HASHITERATOR_H_
#define HASHITERATOR_H_

class HashedList;
class Process;

class HashIterator
{
public:
    HashIterator (const HashedList& H);
    ~HashIterator ();

    Process* operator ()();

private:
    HashedList* _list;
    Process* _current;
};

#endif
