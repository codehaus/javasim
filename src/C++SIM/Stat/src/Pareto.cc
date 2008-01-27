/*
 * Copyright (C) 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#include <math.h>

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef PARETO_H_
#  include <Stat/Pareto.h>
#endif

Pareto::Pareto (double gamma, double k)
	       : _gamma(gamma),
		 _k(k)
{
    _kToGamma = pow(_k, _gamma);
}

double Pareto::pdf (double x)
{
    if (x < _k)
    {
	error_stream << WARNING
		     << "Pareto::pdf - invalid value for x." << endl;
	return 0;
    }
    
    return (double) (_kToGamma / pow(x, _gamma+1));
}

double Pareto::cdf (double x)
{
    if (x < _k)
    {
	error_stream << WARNING
		     << "Pareto::cdf - invalid value for x." << endl;
	return 0;
    }

    return (double) (1 - pow(_k/x, _gamma));
}
