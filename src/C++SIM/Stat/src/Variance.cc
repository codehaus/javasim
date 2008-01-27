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

#ifndef VARIANCE_H_
#  include <Stat/Variance.h>
#endif


Variance::Variance () { Variance::reset(); }

Variance::~Variance () {}

void Variance::reset ()
{
    _sqr = 0.0;
    Mean::reset();
}

void Variance::setValue (double value)
{
    _sqr += value*value;
    Mean::setValue(value);
}

double Variance::variance () const
{
    return ((_Number > 1) ? ((_sqr - ((_Sum * _Sum) / _Number)) / (_Number -1)) : 0.0);
}

double Variance::confidence (double)
{
    error_stream << WARNING << "Variance::confidence not implemented yet." << endl;
    return 0.0;
}

Boolean Variance::saveState (ofstream& oFile) const
{
    if (!oFile)
	return FALSE;

    oFile << " " << _sqr;
    return Mean::saveState(oFile);
}

Boolean Variance::saveState (const char* fileName) const
{
    ofstream oFile(fileName, ios::out);
    Boolean result;
    
    if (!oFile)
    {
	error_stream << WARNING << "Variance::saveState - error "
		     << errno << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = saveState(oFile);
    oFile.close();
    return result;
}

Boolean Variance::restoreState (ifstream& iFile)
{
    if (!iFile)
	return FALSE;
    
    iFile >> _sqr;

    return Mean::restoreState(iFile);
}

Boolean Variance::restoreState (const char* fileName)
{
    ifstream iFile(fileName, ios::in);
    Boolean result;
    
    if (!iFile)
    {
	error_stream << WARNING << "Variance::restoreState - error "
		     << errno << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = restoreState(iFile);
    iFile.close();
    return result;
}

ostream& Variance::print (ostream& strm) const
{
    strm << "\nVariance          : " << variance() << endl;
    strm << "Standard Deviation: " << stdDev() << endl;

    return Mean::print(strm);
}

#ifdef NO_INLINES
#  define VARIANCE_CC_
#  include <Stat/Variance.n>
#  undef VARIANCE_CC_
#endif
