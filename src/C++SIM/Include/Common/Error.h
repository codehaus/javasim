/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef ERROR_H_
#define ERROR_H_

/*
 *
 * Error reporting routines
 *
 */

#include <iostream.h>

enum ErrorSeverity
{
    FATAL, WARNING
};

#ifdef __GNUG__
#define error_stream ((ostream&)cerr)
#else
#define error_stream cerr
#endif

#include <Common/Error.n>

#endif

