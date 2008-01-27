/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: reset.h,v 1.3 1996/12/09 10:10:13 nmcl Exp $ 
 */

#ifndef RESET_H_
#define RESET_H_

#define RESET_POINT RESET:

#define MONITOR_RESET(x,y,z) { x; \
                             if (y == z) \
			         goto RESET; }


#define CHECK_RESET(y,z) { if (y == z) goto RESET; }

#endif


                           
