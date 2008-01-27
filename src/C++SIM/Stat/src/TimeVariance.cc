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

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef TIMEVARIANCE_H_
#  include <Stat/TimeVariance.h>
#endif


TimeVariance::TimeVariance () { TimeVariance::reset(); }

TimeVariance::~TimeVariance () {}

void TimeVariance::reset ()
{
    first = TRUE;
    startTime = currentValue = 0.0;
    stime = total = 0.0;
    Variance::reset();
}

double TimeVariance::timeAverage () const
{
    if (first || (Process::CurrentTime() - startTime) == 0)
        return 0.0;

    return ((total + area())/(Process::CurrentTime() - startTime));
}

void TimeVariance::store (double value)
{
    currentValue = value;
    stime = Process::CurrentTime();
}

void TimeVariance::setValue (double value)
{
    Variance::setValue(value);

    if (!first)
    {
        total += area();
        if (value == currentValue)
	    return;
    }
    else
    {
        first = FALSE;
	startTime = Process::CurrentTime();
    }

    store(value);
}

Boolean TimeVariance::saveState (ofstream& oFile) const
{
    if (!oFile)
	return FALSE;

    oFile << " " << first;
    oFile << " " << startTime << " " << currentValue;
    oFile << " " << stime << " " << total;
    
    return Variance::saveState(oFile);
}

Boolean TimeVariance::saveState (const char* fileName) const
{
    ofstream oFile(fileName, ios::out);
    Boolean result;
    
    if (!oFile)
    {
	error_stream << WARNING << "TimeVariance::saveState - error " << errno
		     << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = saveState(oFile);
    oFile.close();
    return result;
}

Boolean TimeVariance::restoreState (ifstream& iFile)
{
    if (!iFile)
	return FALSE;
    
    iFile >> first;
    iFile >> startTime >> currentValue;
    iFile >> stime, total;
    
    return TRUE;
}

Boolean TimeVariance::restoreState (const char* fileName)
{
    ifstream iFile(fileName, ios::in);
    Boolean result;
    
    if (!iFile)
    {
	error_stream << WARNING << "TimeVariance::restoreState - error " << errno
		     << " for file " << fileName << endl;
	return FALSE;
    }
    
    result = restoreState(iFile);
    iFile.close();
    return result;
}

#ifdef NO_INLINES
#  define TIMEVARIANCE_CC_
#  include <Stat/TimeVariance.n>
#  undef TIMEVARIANCE_CC_
#endif
