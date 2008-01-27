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

#ifndef HISTOGRAM_H_
#  include <Stat/Histogram.h>
#endif

Histogram::Histogram (long maxIndex, MergeChoice m)
                      : maxSize((maxIndex > 0) ? maxIndex : 2),
			merge(m)
{
}

Histogram::~Histogram () {}


// list is maintained in increasing name size so a < b

double Histogram::compositeName (const Bucket& a, const Bucket& b) const
{
    switch (merge)
    {
    case ACCUMULATE:
    case MAX:
	return b.name;
    case MEAN:
	return ((a.name*a.size() + b.name*b.size())/(a.size() + b.size()));
    case MIN:
	return a.name;
    default:
	break;
    }

    return 0.0;
}

long Histogram::compositeSize (const Bucket& a, const Bucket& b) const
{
    switch (merge)
    {
    case ACCUMULATE:
	return (a.size() + b.size());
    case MEAN:
	return (a.size() + b.size());
    case MAX:
	return b.size();
    case MIN:
	return a.size();
    default:
	break;
    }

    // shouldn't get here!

    error_stream << WARNING << "compositeSize switch error." << endl;
    return 0;
}

void Histogram::mergeBuckets ()
{
    Bucket *newHead = (Bucket*) 0, *ptr = (Bucket*) 0;
    Bucket *index = Head;
    long newLength = 0;
    
    index = PrecisionHistogram::Head;
    
    while (index)
    {
	Bucket *newElement = (Bucket*) 0;
	
	// merge buckets in pairs

	if (index->cdr())
	{
	    newElement = new Bucket(compositeName(*index, *index->cdr()));
	    newElement->numberOfEntries = compositeSize(*index, *index->cdr());

	    // move on to next pair of buckets

	    index = (index->cdr())->cdr();
	}
	else
	    newElement = new Bucket(*index);

	newLength++;
	if (newHead)
	    ptr->setCdr(newElement);
	else
	    newHead = newElement;

	ptr = newElement;
    }

    index = PrecisionHistogram::Head;
    ptr = index;

    while (index)
    {
	ptr = index->cdr();
	delete index;
	index = ptr;
    }
    
    PrecisionHistogram::Head = newHead;
    PrecisionHistogram::length = newLength;
}

void Histogram::setValue (double value)
{
    if ((numberOfBuckets() == maxSize) && (!isPresent(value)))
	mergeBuckets();

    PrecisionHistogram::setValue(value);
}

ostream& Histogram::print (ostream& strm) const
{
    strm << "Maximum number of buckets " << maxSize << "\n";
    strm << "Merge choice is ";
    switch (merge)
    {
    case ACCUMULATE:
	strm << "ACCUMULATE\n";
	break;
    case MEAN:
	strm << "MEAN\n";
	break;
    case MAX:
	strm << "MAX\n";
	break;
    case MIN:
	strm << "MIN\n";
	break;
    }
    
    return PrecisionHistogram::print(strm);
}

Boolean Histogram::saveState (ofstream& oFile) const
{
    if (!oFile)
	return FALSE;

    oFile << maxSize << " " << merge;

    return PrecisionHistogram::saveState(oFile);
}

Boolean Histogram::saveState (const char* fileName) const
{
    ofstream oFile(fileName, ios::out);
    Boolean result;
    
    if (!oFile)
    {
	error_stream << WARNING << "Histogram::saveState - error " << errno
		     << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = saveState(oFile);
    oFile.close();
    return result;
}

Boolean Histogram::restoreState (ifstream& iFile)
{
    if (!iFile)
	return FALSE;

    int temp = -1;
    
    iFile >> maxSize >> temp;
    merge = (MergeChoice) temp;

    return PrecisionHistogram::restoreState(iFile);
}

Boolean Histogram::restoreState (const char* fileName)
{
    ifstream iFile(fileName, ios::in);
    Boolean result;
    
    if (!iFile)
    {
	error_stream << WARNING << "Histogram::restoreState - error " << errno
		     << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = restoreState(iFile);
    iFile.close();
    return result;
}

#ifdef NO_INLINES
#  define HISTOGRAM_CC_
#  include <Stat/Histogram.n>
#  undef HISTOGRAM_CC_
#endif
