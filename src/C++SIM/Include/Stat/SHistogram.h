/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef SHISTOGRAM_H_
#define SHISTOGRAM_H_

#ifndef PHISTOGRAM_H_
#  include <Stat/PHistogram.h>
#endif


class SimpleHistogram : public PrecisionHistogram
{
public:
    SimpleHistogram (double min, double max, long nbuckets);
    SimpleHistogram (double min, double max, double w);
    virtual ~SimpleHistogram ();
    
    virtual void setValue (double);
    virtual void operator+= (double);

    virtual void reset ();

    virtual Boolean sizeByName (double name, double& size);
    double  Width () const;

    virtual ostream& print (ostream&) const;
    
private:
    double minIndex, maxIndex;
    double width;
    long numberBuckets;

public:
    virtual Boolean saveState (const char*) const;
    virtual Boolean saveState (ofstream&) const;
    
    virtual Boolean restoreState (const char*);
    virtual Boolean restoreState (ifstream&);
};

#include <Stat/SHistogram.n>

#endif
