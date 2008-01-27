/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <errno.h>
#include <iostream.h>
#include <fstream.h>
#include <iomanip.h>

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef PHISTOGRAM_H_
#  include <Stat/PHistogram.h>
#endif


// the buckets a histogram uses

Bucket::Bucket (double n, long initEntries)
               : numberOfEntries(initEntries),
		 name(n),
		 next(0)
{
}

Bucket::Bucket (const Bucket& b)
	       : next(0)
{
    numberOfEntries = b.numberOfEntries;
    name = b.name;
}

Bucket::~Bucket () {}


// the actual histogram class

PrecisionHistogram::PrecisionHistogram ()
				       : length(0),
					 Head(0)
{
    PrecisionHistogram::reset();
}

PrecisionHistogram::~PrecisionHistogram () { PrecisionHistogram::reset(); }

void PrecisionHistogram::reset ()
{
    if (length > 0)  // delete old list
    {
	Bucket* trail = Head;
	for (long i = 0; i < length; i++)
	{
	    Head = Head->cdr();
	    delete trail;
	    trail = Head;
	}
	
	length = 0;
	Head = (Bucket*) 0;
    }
    
    Variance::reset();
}

// create a new bucket with the given name if one does not exist.

void PrecisionHistogram::create (double value)
{
    Bucket* trail = (Bucket*) 0;
    
    for (Bucket* ptr = Head; ptr; trail = ptr, ptr = ptr->cdr())
    {
	if (*ptr == value)
	    return;
	else
	    if (*ptr > value)  // bucket is not present
		break;
    }
    
    add(trail, value, TRUE);
}

// if createOnly then we want an empty bucket

void PrecisionHistogram::add (Bucket* addPosition, double value,
			      Boolean createOnly)
{
    long initEntries = ((createOnly) ? 0 : 1);
    Bucket* newBucket = new Bucket(value, initEntries);

    if (addPosition == (Bucket*) 0)  // head of list
    {
	newBucket->setCdr(Head);
	Head = newBucket;
    }
    else
    {
	newBucket->setCdr(addPosition->cdr());
	addPosition->setCdr(newBucket);
    }

    length++;
}

Boolean PrecisionHistogram::sizeByName (double name, double& size)
{
    for (Bucket* ptr = Head; ptr; ptr = ptr->cdr())
    {
        if (*ptr == name)
	{
	    size = ptr->size();
	    return TRUE;
	}

	if (*ptr > name)  // bucket is not present
	    break;
    }

    return FALSE;
}

Boolean PrecisionHistogram::sizeByIndex (long index, double& size)
{
    Bucket* ptr = Head;

    if ((index < 0) || (index > length))
        return FALSE;

    for (long i = 0; (i < index) && ptr; i++)
        ptr = ptr->cdr();
    
    if (ptr)
    {
        size = ptr->size();
	return TRUE;
    }

    // we should never get here!

    error_stream << WARNING
		 << "PrecisionHistogram::sizeByIndex went off end of list."
		 << endl;

    return FALSE;
}

Boolean PrecisionHistogram::bucketName (long index, double& name)
{
    Bucket* ptr = Head;

    for (long i = 0; (i < index) && (ptr != 0); i++)
        ptr = ptr->cdr();

    if (ptr != 0)
    {
	name = ptr->Name();
	return TRUE;
    }
    else
	return FALSE;
}

void PrecisionHistogram::setValue (double value)
{
    Variance::setValue(value);

    Bucket* trail = (Bucket*) 0;
    
    for (Bucket* ptr = Head; ptr; trail = ptr, ptr = ptr->cdr())
    {
	if (*ptr == value)
	{
	    (*ptr) += 1;
	    return;
	}
	else if (*ptr > value)
	    break;
    }
    
    // we need to add a new bucket.

    add(trail, value);
}

ostream& PrecisionHistogram::print (ostream& strm) const
{
    if (length == 0)
	strm << "Empty histogram\n";
    else
	for (Bucket* ptr = Head; ptr; ptr = ptr->cdr())
	    strm << "Bucket : < " << ptr->name << ", "
		 << ptr->size() << " >\n";

    return Variance::print(strm);
}

Boolean PrecisionHistogram::saveState (ofstream& oFile) const
{
    if (!oFile)
	return FALSE;

    oFile << " " << length;
    for (Bucket* ptr = Head; ptr; ptr = ptr->cdr())
	oFile << " " << ptr->name << " " << ptr->size();
    
    return Variance::saveState(oFile);
}

Boolean PrecisionHistogram::saveState (const char* fileName) const
{
    ofstream oFile(fileName, ios::out);
    Boolean result;
    
    if (!oFile)
    {
	error_stream << WARNING << "PrecisionHistogram::saveState - error " << errno
		     << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = saveState(oFile);
    oFile.close();
    return result;
}

Boolean PrecisionHistogram::restoreState (ifstream& iFile)
{
    long numberEntries;
    double bucketName;
    Bucket* ptr = (Bucket*) 0;
    
    if (!iFile)
	return FALSE;
    
    PrecisionHistogram::reset();
    
    iFile >> length;
    
    for (int i = 0; i < length; i++)
    {
	iFile >> bucketName >> numberEntries;
	Bucket* toAdd = new Bucket(bucketName, numberEntries);
	if (Head)
	    ptr->next = toAdd;
	else
	    Head = toAdd;

	ptr = toAdd;
    }

    return Variance::restoreState(iFile);
}

Boolean PrecisionHistogram::restoreState (const char* fileName)
{
    ifstream iFile(fileName, ios::in);
    Boolean result;
    
    if (!iFile)
    {
	error_stream << WARNING
		     << "PrecisionHistogram::restoreState - error " << errno
		     << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = restoreState(iFile);
    iFile.close();
    return result;
}


#ifdef NO_INLINES
#  define PHISTOGRAM_CC_
#  include <Stat/PHistogram.n>
#  undef PHISTOGRAM_CC_
#endif
