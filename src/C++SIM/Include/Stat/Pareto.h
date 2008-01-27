/*
 * Copyright (C) 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef PARETO_H_
#define PARETO_H_

class Pareto
{
public:
    Pareto (double gamma, double k = 1.0);

    double pdf (double x);
    double cdf (double x);
    
private:
    double _gamma;
    double _k;
    double _kToGamma;
};

#endif
