/*
 * Copyright (C) 1994, 1995, 1996, 1997
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Controller.h,v 1.1 1996/12/09 10:10:05 nmcl Exp $
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

class Controller : public Process
{
public:
    Controller ();
    ~Controller ();

    void Body ();

    void Await ();
    void Exit ();
};

#endif
