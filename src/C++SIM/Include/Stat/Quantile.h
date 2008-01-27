/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef QUANTILE_H_
#define QUANTILE_H_

#ifndef PHISTOGRAM_H_
#  include <Stat/PHistogram.h>
#endif


class Quantile : public PrecisionHistogram
{
public:
    Quantile (double = 0.95);
    virtual ~Quantile ();

    double operator() () const;
    double range () const;

    virtual ostream& print (ostream&) const;

private:
    double qProb;
};

#include <Stat/Quantile.n>

#endif
