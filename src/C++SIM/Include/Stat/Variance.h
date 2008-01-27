/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef VARIANCE_H_
#define VARIANCE_H_

#ifndef MEAN_H_
#  include <Stat/Mean.h>
#endif


class Variance : public Mean
{
public:
    Variance ();
    virtual ~Variance ();
     
    virtual void setValue (double);
    virtual void operator+= (double);

    virtual void reset ();

    double variance () const;
    double stdDev () const;

    double confidence (double);

    virtual ostream& print (ostream&) const;
    
protected:
    double _sqr;

public:
    virtual Boolean saveState (const char*) const;
    virtual Boolean saveState (ofstream&) const;
    
    virtual Boolean restoreState (const char*);
    virtual Boolean restoreState (ifstream&);
};


#include <Stat/Variance.n>

#endif

