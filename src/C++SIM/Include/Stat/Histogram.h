/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef HISTOGRAM_H_
#define HISTOGRAM_H_

#ifndef PHISTOGRAM_H_
#  include <Stat/PHistogram.h>
#endif


/*
 * This histogram class maintains a fixed number of buckets.
 * When the number of buckets required to maintain all of the
 * values given is about to be exceeded a merge operation is
 * performed. This takes a pair of buckets and merges their values
 * according to the policy selected when the histogram was created.
 * The policies are:
 *
 * (1) ACCUMULATE - this creates a new bucket with the same name as
 *     the largest of the buckets, and it has the sum of the two
 *     old bucket entries as its entry number.
 * (2) MEAN - this creates a new bucket with the name as the mean of
 *     the two old buckets, and it has the sum of the two old bucket
 *     entries as its entry number.
 * (3) MAX - this creates a new bucket with the name as the largest of
 *     the buckets, and it has the same number of entries.
 * (4) MIN - this creates a new bucket with the name as the smallest of
 *     the two buckets, and it has the same number of entries.
 */

class Histogram : public PrecisionHistogram
{
public:
    enum MergeChoice { ACCUMULATE, MEAN, MAX, MIN };
	
    Histogram (long, MergeChoice = MEAN);
    virtual ~Histogram ();
    
    virtual void setValue (double);
    virtual void operator+= (double);

    virtual ostream& print (ostream&) const;

protected:
    virtual void mergeBuckets ();
    
private:
    double compositeName (const Bucket&, const Bucket&) const;
    long compositeSize (const Bucket&, const Bucket&) const;

    long maxSize;
    MergeChoice merge;

public:
    virtual Boolean saveState (const char*) const;
    virtual Boolean saveState (ofstream&) const;
    
    virtual Boolean restoreState (const char*);
    virtual Boolean restoreState (ifstream&);
};

#include <Stat/Histogram.n>

#endif
