/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Timer.cc,v 1.3 1997/03/18 13:47:32 nmcl Exp $
 */

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef TESTER_H_
#  include "Tester.h"
#endif

#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include <sys/time.h>
#include <unistd.h>

#ifdef SYSV
#  include <sys/times.h>
#  include <limits.h>
#endif

#ifdef __GNUG__
extern "C"
{
    int gettimeofday (struct timeval*, struct timezone*);
}
#endif

#ifdef SYSV
const double clockTick = (1.0/sysconf(_SC_CLK_TCK));
#endif

int main (int argc, char** argv)
{
    long numberOfProcesses = 100;
    long iterations = 100000;
    extern long numberOfJobs;
    int hold = 0;
    
#ifdef SYSV
    clock_t currentTime = 0, startTime = 0;
    struct tms ClockBuffer;
#else
    unsigned long start_ms, finish_ms;
    struct timeval stime, ftime;
#endif

    for (int i = 0; i < argc; i++)
    {
        if (::strcmp(argv[i], "-help") == 0)
	{
	    cout << "Usage: " << argv[0] << " [-number <number>] [-iter <iterations>] [-help] [-hold]" << endl;
	    return 0;
	}
	if (::strcmp(argv[i], "-number") == 0)
	    numberOfProcesses = atol(argv[i+1]);
	if (::strcmp(argv[i], "-iter") == 0)
	    iterations = atol(argv[i+1]);
	if (::strcmp(argv[i], "-hold") == 0)
	    hold = 1;
    }

    Thread::Initialize();
   
    Tester t(numberOfProcesses, iterations, hold);

#ifdef SYSV
    startTime = times(&ClockBuffer);
    double convertTime = 0.0;
#else
    gettimeofday(&stime, 0);
    start_ms = stime.tv_sec*1000000 + stime.tv_usec;
#endif

    t.Await();

#ifdef SYSV
    currentTime = times(&ClockBuffer) - startTime;
    convertTime = currentTime * clockTick * 1000000;
#else
    gettimeofday(&ftime, 0);
    finish_ms = ftime.tv_sec * 1000000 + ftime.tv_usec;
#endif

    cout << "Time to perform " << numberOfJobs << " operations was ";

#ifdef SYSV
    cout << (long) (convertTime/1000);
#else
    cout << (long) ((finish_ms - start_ms)/1000);
#endif

    cout << " milliseconds" << endl;

    t.Exit();
    
    return 0;
}
