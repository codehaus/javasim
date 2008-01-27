/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Boolean.h,v 1.2 1996/12/02 14:19:24 nmcl Exp $
 */

#ifndef BOOLEAN_H_
#define BOOLEAN_H_

/* first check for TRUE and FALSE definitions - if so then undefine them */

#ifdef TRUE
#  undef TRUE
#  undef FALSE
#endif

/* For C++ usage */

#ifndef HAVE_BOOLEAN_TYPE
typedef unsigned short Boolean;

extern const Boolean TRUE;
extern const Boolean FALSE;
#else

typedef bool Boolean;

#  define TRUE true
#  define FALSE false
#endif

#endif

