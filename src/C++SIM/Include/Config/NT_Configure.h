/*
 * Copyright (C) 1993
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: NT_Configure.h,v 1.4 1997/07/31 11:21:42 nmcl Exp $
 */

#ifndef NT_CONFIGURE_H_
#define NT_CONFIGURE_H_

/*
 * You will need to define NT_THREAD and ProcessList_Queue as
 *  part of the cpp flags.
 */

#define Thread_Type NT_Thread
#define LINEAR 1
#define Queue_Type ProcessList

#endif
