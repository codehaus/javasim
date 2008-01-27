/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef TIMEVARIANCE_H_
#define TIMEVARIANCE_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef VARIANCE_H_
#  include <Stat/Variance.h>
#endif


class TimeVariance : public Variance
{
public:
    TimeVariance ();
    ~TimeVariance ();

    virtual void reset ();

    virtual void setValue (double);
    virtual void operator+= (double);

    double timeAverage () const;

protected:
    double area () const;

    Boolean first;
    double startTime, currentValue;
    double stime, total;

private:
    void store (double);

public:
    virtual Boolean saveState (const char*) const;
    virtual Boolean saveState (ofstream&) const;
    
    virtual Boolean restoreState (const char*);
    virtual Boolean restoreState (ifstream&);
};

#include <Stat/TimeVariance.n>

#endif
