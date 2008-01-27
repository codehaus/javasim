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
#include <values.h>
#include <iomanip.h>

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef MEAN_H_
#  include <Stat/Mean.h>
#endif

Mean::Mean () { Mean::reset(); }

Mean::~Mean () {}

void Mean::reset ()
{
    _Max = -MAXFLOAT;
    _Min = MAXFLOAT;
    _Sum = _Mean = 0.0;
    _Number = 0;
}

void Mean::setValue (double value)
{
    if (value > _Max)
        _Max = value;
    if (value < _Min)
        _Min = value;
    _Sum += value;
    _Number++;
    _Mean = (double) (_Sum/_Number);
}

Boolean Mean::saveState (ofstream& oFile) const
{
    if (!oFile)
	return FALSE;
    
    oFile << " " << _Max << " " << _Min;
    oFile << " " << _Sum << " " << _Mean;
    oFile << " " << _Number << " ";
    return TRUE;
}

Boolean Mean::saveState (const char* fileName) const
{
    ofstream oFile(fileName, ios::out);
    Boolean result;
    
    if (!oFile)
    {
	error_stream << WARNING << "Mean::saveState - error " << errno << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = saveState(oFile);
    oFile.close();
    return result;
}

Boolean Mean::restoreState (ifstream& iFile)
{
    if (!iFile)
	return FALSE;
    
    iFile >> _Max >> _Min;
    iFile >> _Sum >> _Mean;
    iFile >> _Number;
    return TRUE;
}

Boolean Mean::restoreState (const char* fileName)
{
    ifstream iFile(fileName, ios::in);
    Boolean result;
    
    if (!iFile)
    {
	error_stream << WARNING << "Mean::restoreState - error " << errno << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = restoreState(iFile);
    iFile.close();
    return result;
}

ostream& Mean::print (ostream& strm) const
{
    strm << "Number of samples : " << numberOfSamples() << endl;
    strm << "Minimum           : " << min() << endl;
    strm << "Maximum           : " << max() << endl;
    strm << "Sum               : " << sum() << endl;
    strm << "Mean              : " << mean() << endl;

    return strm;
}

#ifdef NO_INLINES
#  define MEAN_CC_
#  include <Stat/Mean.n>
#  undef MEAN_CC_
#endif
