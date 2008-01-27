/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */


#include <iostream.h>
#include <stdlib.h>

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif


#ifdef NO_INLINES
#  define ERROR_CC_
#  include <Common/Error.n>
#  undef ERROR_CC_
#endif
