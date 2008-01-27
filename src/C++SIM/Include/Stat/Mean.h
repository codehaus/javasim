/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef MEAN_H_
#define MEAN_H_

#include <iostream.h>
#include <fstream.h>

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif


class Mean
{
public:
    Mean ();
    virtual ~Mean ();

    virtual void setValue (double);
    virtual void operator+= (double);

    virtual void reset ();

    unsigned int numberOfSamples () const;

    double min () const;
    double max () const;
    double sum () const;
    double mean () const;

    virtual ostream& print (ostream&) const;    
    
protected:
    double _Max, _Min;
    double _Sum, _Mean;
    unsigned int _Number;

public:
    virtual Boolean saveState (const char*) const;
    virtual Boolean saveState (ofstream&) const;
    
    virtual Boolean restoreState (const char*);
    virtual Boolean restoreState (ifstream&);
};

#include <Stat/Mean.n>

#endif
