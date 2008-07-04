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

package org.javasim;

public class Semaphore
{

    /**
     * Create a new mutex (resources = 1).
     */

    public Semaphore()
    {
        numberWaiting = 0;
        numberOfResources = 1;
        currentResources = 1;
    }

    /**
     * Create a new semaphore (resources = number).
     */

    public Semaphore(long number)
    {
        numberWaiting = 0;
        numberOfResources = number;
        currentResources = number;
    }

    public void finalize ()
    {
        if (numberWaiting != 0)
            System.out
                    .println("Warning: semaphore being removed with clients waiting.");
    }

    /**
     * Number of entities blocked on the semaphore.
     */

    public synchronized long NumberWaiting ()
    {
        return numberWaiting;
    }

    /**
     * Try to acquire the semaphore. Caller will be blocked if there are no free
     * resources.
     */

    public synchronized int Get (SimulationEntity toWait)
            throws RestartException
    {
        if (currentResources > 0)
            currentResources--;
        else
        {
            numberWaiting++;

            try
            {
                waitingList.insert(toWait);
            }
            catch (SimulationException e)
            {
            }

            toWait.Cancel();
        }

        return SemaphoreOutcome.DONE;
    }

    /**
     * Only acquire the semaphore if it would not block the caller.
     */

    public synchronized int TryGet (SimulationEntity toWait)
            throws RestartException
    {
        if (currentResources == 0)
            return SemaphoreOutcome.WOULD_BLOCK;
        else
            return Get(toWait);
    }

    /**
     * Release the semaphore. No check is made to ensure the caller has
     * previously acquired the semaphore.
     */

    public synchronized int Release ()
    {
        if (numberWaiting > 0)
        {
            currentResources++;

            if (currentResources > numberOfResources)
                currentResources = numberOfResources;

            numberWaiting--;

            // don't set trigger flag - not strictly a trigger

            waitingList.triggerFirst(false);

            return SemaphoreOutcome.DONE;
        }
        else
            return SemaphoreOutcome.NOTDONE;
    }

    private TriggerQueue waitingList;

    private long numberWaiting;

    private long numberOfResources;

    private long currentResources;

};
