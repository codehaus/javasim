/*
 * Copyright (C) 1996, 1997, 1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Scheduler.java,v 1.3 1998/12/07 08:28:10 nmcl Exp $
 */

package arjuna.JavaSim.Simulation;

import java.util.NoSuchElementException;

public class Scheduler extends Thread
{

    /**
      Return the current simulation time.
      */
    
    public static double CurrentTime ()
    {
	return Scheduler.SimulatedTime;
    }

    /**
     * This routine resets the simulation time to zero and removes all
     * entries from the scheduler queue (as their times may no longer
     * be valid). Whatever operation caused the processes to become
     * suspended will raise the RestartSimulation exception, which the
     * application should catch. It should then perform any work necessary
     * to put the process back in a state ready for restarting the simulation
     * before calling Cancel on the process.
     */
    
    public static synchronized void reset () throws SimulationException
    {
	boolean finished = false;
	SimulationProcess tmp = SimulationProcess.current();
	
	Scheduler._simulationReset = true;

	// set resetting process to idle

	Scheduler.unschedule(tmp); // remove from queue
	tmp.passivate();

	do
	{
	    try
	    {
		tmp = Scheduler.ReadyQueue.Remove();
	    }
	    catch (NoSuchElementException e)
	    {
		finished = true;
	    }
	    
	} while (!finished);
	
	finished = false;

	SimulationProcessIterator iter = new SimulationProcessIterator(SimulationProcess.allProcesses);
	
	do
	{
	    try
	    {
		tmp = iter.get();

		/*
		 * Every process must be in Suspend, so we call Resume
		 * and get each one to check whether the simulation is
		 * restarting. If it is, it raises an exception and waits
		 * for the user to cancel the process after setting it
		 * to become ready to restart.
		 */
		
		tmp.Resume();

		/*
		 * Wait for this process to become idle again.
		 */
		
		while (!tmp.idle())
		    Thread.yield();
	    }
	    catch (NullPointerException e)
	    {
		finished = true;
	    }
		
	} while (!finished);

	Scheduler.SimulatedTime = 0.0;
	Scheduler._simulationReset = false;

	SimulationProcess.Current = null;
    }

    /**
     * Is the simulation undergoing a reset? Processes should call this
     * method to determine whether the simulation is being reset. If it
     * is, then they should act accordingly.
     */
    
    public static synchronized boolean simulationReset ()
    {
	return Scheduler._simulationReset;
    }
    
    /**
     * Stop the simulation. Processes should call this
     * method to determine whether the simulation is being stopped. If it
     * is, then they should act accordingly.
     */
    
    public static synchronized void stopSimulation ()
    {
	Scheduler.schedulerRunning = false;
    }

    /**
     * Start the simulation either from the start or from where it was
     * previously stopped.
     */
    
    public static synchronized void startSimulation ()
    {
	Scheduler.schedulerRunning = true;
    }

    protected static synchronized boolean simulationStarted ()
    {
	return Scheduler.schedulerRunning;
    }

    private Scheduler ()
    {
    }

    /**
     * It is possible that the currently active process may remove itself
     * from the simulation queue. In which case we don't want to suspend the
     * process since it needs to continue to run. The return value indicates
     * whether or not to call suspend on the currently active process.
     */
    
    static synchronized boolean schedule () throws SimulationException
    {
	if (Scheduler.simulationStarted())
	{
	    SimulationProcess p = SimulationProcess.current();
	    
	    try
	    {
		SimulationProcess.Current = Scheduler.ReadyQueue.Remove();
	    }
	    catch (NoSuchElementException e)
	    {
		System.out.println("Simulation queue empty - terminating.");
		System.exit(0);
	    }

	    if (SimulationProcess.Current.evtime() < 0)
		throw new SimulationException("Invalid SimulationProcess wakeup time.");
	    else
		Scheduler.SimulatedTime = SimulationProcess.Current.evtime();

	    if (p != SimulationProcess.Current)
	    {
		SimulationProcess.Current.Resume();
		
		return true;
	    }
	    else
		return false;
	}
	else
	    throw new SimulationException("Simulation not started.");
    }

    static synchronized void unschedule (SimulationProcess p)
    {
	try
	{
	    Scheduler.ReadyQueue.Remove(p); // remove from queue
	}
	catch (NoSuchElementException e)
	{
	}

	p.passivate();
    }

    static SimulationProcessList getQueue ()
    {
	synchronized (theScheduler)
	{
	    return ReadyQueue;
	}
    }

    static double getSimulationTime ()
    {
	synchronized (theScheduler)
	{
	    return SimulatedTime;
	}
    }
    
    private static double SimulatedTime = 0.0;
    private static SimulationProcessList ReadyQueue = new SimulationProcessList();
    
    private static boolean schedulerRunning = false;
    private static boolean _simulationReset = false;

    static Scheduler theScheduler = new Scheduler();
    
}
