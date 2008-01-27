/*
 * Copyright (C) 1993, 1994, 1995, 1996
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id$
 */

/*
 *  Configure.h
 */

#ifndef CONFIGURE_H_
#  define CONFIGURE_H_
#include <Config/m_unknown.cf>
#include <Config/v_unknown.cf>
#include <Config/s_unknown.cf>
#include <Config/c_gcc_2_7.cf>

#define OSNAME CYGWIN_NT-5.1
#define OSRELEASE 1.3.2(0.39/3/2)
#define OSMAJOR 1
#define OSMINOR 3
#define MACHINE_HW "i686"


#define CPLUSPLUS_CROSS_PROGRAM ""

#ifndef YES
#define YES 1
#endif

#ifndef NO
#define NO  0
#endif

/*
 *  Make and Source configuration
 */

#ifndef VERBOSE_MAKE
#define VERBOSE_MAKE NO
#endif

#ifndef TOPDIR_DEFAULT
#define TOPDIR_DEFAULT //c/Projects/C++SIM
#endif

#ifndef PURIFY_PROGRAM
#define PURIFY_PROGRAM  "exec"
#endif

#ifndef CPLUSPLUS_PROGRAM
#define CPLUSPLUS_PROGRAM  "gcc"
#endif

#ifndef CPLUSPLUS_INCLUDE_DEFAULT
#define CPLUSPLUS_INCLUDE_DEFAULT /usr/include/g++-3
#endif

#ifndef CPPFLAGS_DEFAULT
#define CPPFLAGS_DEFAULT 
#endif

#ifndef CPLUSPLUSFLAGS_DEFAULT
#define CPLUSPLUSFLAGS_DEFAULT 
#endif

#ifndef LDFLAGS_DEFAULT
#define LDFLAGS_DEFAULT 
#endif

#ifndef xLIBRARIES_DEFAULT
#define xLIBRARIES_DEFAULT  -lm
#endif

#ifndef BUILDFLAGS_DEFAULT
#define BUILDFLAGS_DEFAULT  -DProcessList_Queue
#endif

/*
 *  Thread system details
 */


/*
 *  Scheduler queue details
 */

#define LINEAR 1
#define HEAP 2
#define CALENDAR 3
#define HASHED 4

#ifndef Queue_Type
#define Queue_Type ProcessList
#endif

/*
 *  Thread system details
 */

#ifndef THREAD_TYPE
#define THREAD_TYPE Rex_Thread
#endif

#ifndef THREAD_CPPFLAGS_DEFAULT
#define THREAD_CPPFLAGS_DEFAULT  -DREX_THREAD
#endif

#ifndef COMPILER_THREAD_FLAGS_DEFAULT
#define COMPILER_THREAD_FLAGS_DEFAULT 
#endif

#ifndef THREAD_LDFLAGS_DEFAULT
#define THREAD_LDFLAGS_DEFAULT 
#endif

#ifndef THREAD_LDLIBS_DEFAULT
#define THREAD_LDLIBS_DEFAULT  -llwp
#endif

/*
 *  Installation details
 */

#ifndef INSTALL_TOPDIR_DEFAULT
#define INSTALL_TOPDIR_DEFAULT /usr/local/C++SIM
#endif

#endif
