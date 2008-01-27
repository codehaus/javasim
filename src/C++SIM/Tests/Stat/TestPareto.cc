/*
 * Copyright (C) 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <string.h>
#include <iostream.h>
#include <stdlib.h>

#ifndef PARETO_H_
#  include <Stat/Pareto.h>
#endif

int main (int argc, char** argv)
{
    double k = 1.0;
    double gamma = 1.0;
    
    for (int i = 0; i < argc; i++)
    {
        if (::strcmp(argv[i], "-help") == 0)
	{
	    cout << "Usage: " << argv[0] << " [-gamma <value>] [-k <value>] [-help]" << endl;
	    return 0;
	}
	if (::strcmp(argv[i], "-k") == 0)
	    k = atof(argv[i+1]);
	if (::strcmp(argv[i], "-gamma") == 0)
	    gamma = atof(argv[i+1]);
    }

    Pareto p(gamma, k);

    for (int j = 1; j < 10; j++)
	cout << j << " " << p.cdf(j) << endl;

    return 0;
}
