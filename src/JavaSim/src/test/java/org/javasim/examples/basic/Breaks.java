/*
 * Copyright 1990-2008, Mark Little, University of Newcastle upon Tyne
 * and others contributors as indicated 
 * by the @authors tag. All rights reserved. 
 * See the copyright.txt in the distribution for a
 * full listing of individual contributors. 
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU Lesser General Public License, v. 2.1.
 * This program is distributed in the hope that it will be useful, but WITHOUT A 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License,
 * v.2.1 along with this distribution; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, 
 * MA  02110-1301, USA.
 * 
 * (C) 1990-2008,
 */

import arjuna.JavaSim.Simulation.*;
import arjuna.JavaSim.Distributions.*;

import java.io.IOException;
import arjuna.JavaSim.Simulation.SimulationException;

public class Breaks extends SimulationProcess
{
    
public Breaks ()
    {
	RepairTime = new UniformStream(10, 100);
	OperativeTime = new UniformStream(200, 500);
	interrupted_service = false;
    }

public void run ()
    {
	for(;;)
	{
	    try
	    {
		double failedTime = RepairTime.getNumber();
		
		Hold(OperativeTime.getNumber());

		MachineShop.M.Broken();
		MachineShop.M.Cancel();

		if(!MachineShop.JobQ.IsEmpty())
		    interrupted_service = true;

		Hold(failedTime);

		MachineShop.MachineFailedTime += failedTime;
		MachineShop.M.Fixed();
	
		if (interrupted_service)
		    MachineShop.M.ActivateAt(MachineShop.M.ServiceTime() + CurrentTime());
		else
		    MachineShop.M.Activate();
		
		interrupted_service = false;
	    }
	    catch (SimulationException e)
	    {
	    }
	    catch (RestartException e)
	    {
	    }
	    catch (IOException e)
	    {
	    }
	}	
    }

private UniformStream RepairTime;
private UniformStream OperativeTime;
private boolean interrupted_service;
    
};
