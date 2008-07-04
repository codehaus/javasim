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

package org.javasim.stats;

import java.io.*;
import java.lang.IllegalArgumentException;

import org.javasim.SimulationProcess;

/**
 * Obtain the average value given during the simulation time.
 */

public class TimeVariance extends Variance
{

    public TimeVariance()
    {
        reset();
    }

    /**
     * Zero the statistics.
     */

    public void reset ()
    {
        first = true;
        startTime = currentValue = 0.0;
        stime = total = 0.0;
        super.reset();
    }

    /**
     * Add 'value', updating the statistics.
     */

    public void setValue (double value) throws IllegalArgumentException
    {
        super.setValue(value);

        if (!first)
        {
            total += area();
            if (value == currentValue)
                return;
        }
        else
        {
            first = false;
            startTime = SimulationProcess.CurrentTime();
        }

        store(value);
    }

    /**
     * Return the average value given up to the current simulation time.
     */

    public double timeAverage ()
    {
        if (first || (SimulationProcess.CurrentTime() - startTime) == 0)
            return 0.0;

        return ((total + area()) / (SimulationProcess.CurrentTime() - startTime));
    }

    /**
     * Save the state of the histogram to the file named 'fileName'.
     */

    public boolean saveState (String fileName) throws IOException
    {
        FileOutputStream f = new FileOutputStream(fileName);
        DataOutputStream oFile = new DataOutputStream(f);

        boolean res = saveState(oFile);

        f.close();

        return res;
    }

    /**
     * Save the state of the histogram to the stream 'oFile'.
     */

    public boolean saveState (DataOutputStream oFile) throws IOException
    {
        oFile.writeBoolean(first);
        oFile.writeDouble(startTime);
        oFile.writeDouble(currentValue);
        oFile.writeDouble(stime);
        oFile.writeDouble(total);

        return super.saveState(oFile);
    }

    /**
     * Restore the histogram state from the file 'fileName'.
     */

    public boolean restoreState (String fileName) throws FileNotFoundException,
            IOException
    {
        FileInputStream f = new FileInputStream(fileName);
        DataInputStream iFile = new DataInputStream(f);

        boolean res = restoreState(iFile);

        f.close();

        return res;
    }

    /**
     * Restore the histogram state from the stream 'iFile'.
     */

    public boolean restoreState (DataInputStream iFile) throws IOException
    {
        first = iFile.readBoolean();
        startTime = iFile.readDouble();
        currentValue = iFile.readDouble();
        stime = iFile.readDouble();
        total = iFile.readDouble();

        return true;
    }

    private double area ()
    {
        return (currentValue * (SimulationProcess.CurrentTime() - stime));
    }

    private void store (double value)
    {
        currentValue = value;
        stime = SimulationProcess.CurrentTime();
    }

    private boolean first;

    private double startTime;

    private double currentValue;

    private double stime;

    private double total;

};
