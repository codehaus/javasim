#include <iostream.h>

#ifndef PROCESS_H_
#  include <ClassLib/Process.h>
#endif

#ifndef RESET_H_
#  include <ClassLib/reset.h>
#endif

#ifndef HARNESS_H_
#  include "Harness.h"
#endif


Harness::Harness ()
		 : status(FALSE),
		   _doPassivate(FALSE)
{
}

Harness::~Harness () {}

void Harness::Body ()
{
    status = TRUE;
    RESET_POINT;   // the ';' is optional

    if (_doPassivate)
    {
	cout << "\tHarness passivated." << endl;
	Passivate();
    }
    
    cout << "\tHarness holding." << endl;
    Hold(10);

    cout << "\tHarness holding and checking." << endl;
    MONITOR_RESET(Hold(1000), status, FALSE); // the ';' is optional

    /*
     * The following is just as valid as the previous
     * MONITOR_RESET
     *
     * Hold(1000);
     * CHECK_RESET(status, FALSE);
     */
    
    cout << "\tHarness passivated." << endl;
    Passivate();
}

void Harness::reset ()
{
    cout << "\tHarness reset function called." << endl;
    
    status = FALSE;
}

void Harness::doPassivate ()
{
    _doPassivate = TRUE;
}
