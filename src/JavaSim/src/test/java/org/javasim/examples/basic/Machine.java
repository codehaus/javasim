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

package org.javasim.examples.basic;

import java.io.IOException;

import org.javasim.RestartException;
import org.javasim.SimulationException;
import org.javasim.SimulationProcess;
import org.javasim.streams.ExponentialStream;

public class Machine extends SimulationProcess
{

    public Machine(double mean)
    {
        STime = new ExponentialStream(mean);
        operational = true;
        working = false;
        J = null;
    }

    public void run ()
    {
        double ActiveStart, ActiveEnd;

        for (;;)
        {
            working = true;

            while (!MachineShop.JobQ.IsEmpty())
            {
                ActiveStart = CurrentTime();
                MachineShop.CheckFreq++;

                MachineShop.JobsInQueue += MachineShop.JobQ.QueueSize();
                J = MachineShop.JobQ.Dequeue();

                try
                {
                    Hold(ServiceTime());
                }
                catch (SimulationException e)
                {
                }
                catch (RestartException e)
                {
                }

                ActiveEnd = CurrentTime();
                MachineShop.MachineActiveTime += ActiveEnd - ActiveStart;
                MachineShop.ProcessedJobs++;

                /*
                 * Introduce this new method because we usually rely upon the
                 * destructor of the object to do the work in C++.
                 */

                J.finished();
            }

            working = false;

            try
            {
                Cancel();
            }
            catch (RestartException e)
            {
            }
        }
    }

    public void Broken ()
    {
        operational = false;
    }

    public void Fixed ()
    {
        operational = true;
    }

    public boolean IsOperational ()
    {
        return operational;
    }

    public boolean Processing ()
    {
        return working;
    }

    public double ServiceTime ()
    {
        try
        {
            return STime.getNumber();
        }
        catch (IOException e)
        {
            return 0.0;
        }
    }

    private ExponentialStream STime;

    private boolean operational;

    private boolean working;

    private Job J;

};
