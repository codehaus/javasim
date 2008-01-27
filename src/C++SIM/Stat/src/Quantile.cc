/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef QUANTILE_H_
#  include <Stat/Quantile.h>
#endif


// if a bad value is given to constructor then default is used

Quantile::Quantile (double q)
		   : qProb(((q > 0.0) && (q <= 1.0)) ? q : 0.95)
{
    if ((q <= 0.0) || (q > 1.0))
	error_stream << WARNING << "Quantile::Quantile ( " << q << " ) : bad value." << endl;
}

Quantile::~Quantile () {}

double Quantile::operator() () const
{
    double pSamples = numberOfSamples() * qProb;
    long nEntries = 0;
    Bucket *ptr = Head, *trail = (Bucket*) 0;

    if (pSamples == 0.0)
    {
	error_stream << WARNING << "Quantile::operator() : percentage samples error." << endl;
	return 0.0;
    }
    
    while ((nEntries < pSamples) && (ptr))
    {
        nEntries += ptr->size();
        trail = ptr;
	ptr = ptr->cdr();
    }

    return trail->Name();
}

ostream& Quantile::print (ostream& strm) const
{
    strm << "Quantile precentage : " << qProb << "\n";
    strm << "Value below which percentage occurs " << (*this)() << "\n";
    return PrecisionHistogram::print(strm);
}


#ifdef NO_INLINES
#  define QUANTILE_CC_
#  include <Stat/Quantile.n>
#  undef QUANTILE_CC_
#endif
