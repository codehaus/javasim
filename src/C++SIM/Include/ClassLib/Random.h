/*
 * Copyright (C) 1994-1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Random.h,v 1.8 1998/10/01 08:20:53 nmcl Exp $
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//  This file contains the interfaces for five different (pseudo-) random    //
//  number  generators:                                                      //
//                                                                           //
//  1) Uniform -          returns a  number drawn from a uniform distribution//
//                        with the given lower and upper bounds.             //
//                                                                           //
//  2) Exponential -      returns a number from an exponential distribution  //
//                        with the given mean                                //
//                                                                           //
//  3) Erlang -           returns a number from an Erlang distribution with  //
//                        the given mean and standard deviation              //
//                                                                           //
//  4) HyperExponential - returns a number from a hyperexpontial distribution//
//                        with the given mean and standard deviation         //
//                                                                           //
//  5) Normal -           returns a number from a normal distribution with   //
//                        the given mean and standard deviation.             //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// The class RandomStream is an abstract base class from which the other     //
// distribution classes are derived.                                         //
///////////////////////////////////////////////////////////////////////////////

class RandomStream
{
public:
    virtual double operator() () = 0;
    double Error ();	// returns a chi-square error measure on the uniform
			// distribution function
    
protected:
    RandomStream (long MGSeed=772531L, long LCGSeed=1878892440L);
    
    double Uniform ();

    void copy (const RandomStream&);
    
private:
    double MGen ();
    
    double series[128];
    long MSeed, LSeed;
};

class UniformStream : public RandomStream
{
public:
    UniformStream (double lo, double hi, int StreamSelect=0,
		   long MGSeed=772531L, long LCGSeed=1878892440L);
    virtual double operator() ();

    UniformStream& operator= (const UniformStream& toCopy);
    
private:
    double lo, hi;
    double range;
};

class Draw
{
public:
    Draw (double p, int StreamSelect=0,
	  long MGSeed=772531L, long LCGSeed=1878892440L);
    virtual Boolean operator() ();

    Draw& operator= (const Draw& toCopy);
    
private:
    UniformStream s;
    double prob;
};

class ExponentialStream : public RandomStream
{
public:
    ExponentialStream (double Mean, int StreamSelect=0,
		       long MGSeed=772531L, long LCGSeed=1878892440L);
    virtual double operator() ();

    ExponentialStream& operator= (const ExponentialStream& toCopy);
    
private:
    double Mean;
};

class ErlangStream : public RandomStream
{
public:
    ErlangStream (double Mean, double StandardDeviation, int StreamSelect=0,
		  long MGSeed=772531L, long LCGSeed=1878892440L);
    virtual double operator() ();

    ErlangStream& operator= (const ErlangStream& toCopy);
    
private:
    double Mean, StandardDeviation;
    long k;
};

class HyperExponentialStream : public RandomStream
{
public:
    HyperExponentialStream (double Mean, double StandardDeviation,
			    int StreamSelect=0,
			    long MGSeed=772531L,long LCGSeed=1878892440L);
    virtual double operator() ();

    HyperExponentialStream& operator= (const HyperExponentialStream& toCopy);
    
private:
    double Mean, StandardDeviation;
    double p;
};

class NormalStream : public RandomStream
{
public:
    NormalStream (double Mean, double StandardDeviation, int StreamSelect=0,
		  long MGSeed=772531L,long LCGSeed=1878892440L);
    virtual double operator() ();

    NormalStream& operator= (const NormalStream& toCopy);
    
private:
    double Mean, StandardDeviation;
    double z;
};
    
#include <ClassLib/Random.n>

#endif // RANDOM_H

