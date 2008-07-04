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

package org.javasim.streams;

import java.lang.Math;

import java.io.IOException;
import java.lang.ArithmeticException;

/**
 * Returns a number from a hyperexpontial distribution with the given mean and
 * standard deviation.
 */

public class HyperExponentialStream extends RandomStream
{

    /**
     * Create stream with mean 'm' and standard deviation 'sd'.
     */

    public HyperExponentialStream(double m, double sd)
    {
        super();

        Mean = m;
        StandardDeviation = sd;

        double cv, z;
        cv = StandardDeviation / Mean;
        z = cv * cv;
        p = 0.5 * (1.0 - Math.sqrt((z - 1.0) / (z + 1.0)));
    }

    /**
     * Create stream with mean 'm' and standard deviation 'sd'. Skip the first
     * 'StreamSelect' values.
     */

    public HyperExponentialStream(double m, double sd, int StreamSelect)
    {
        super();

        Mean = m;
        StandardDeviation = sd;

        double cv, z;
        cv = StandardDeviation / Mean;
        z = cv * cv;
        p = 0.5 * (1.0 - Math.sqrt((z - 1.0) / (z + 1.0)));

        for (int ss = 0; ss < StreamSelect * 1000; ss++)
            uniform();
    }

    /**
     * Create stream with mean 'm' and standard deviation 'sd'. Skip the first
     * 'StreamSelect' values. Pass seeds 'MGSeed' and 'LCGSeed' to the base
     * class.
     */

    public HyperExponentialStream(double m, double sd, int StreamSelect,
            long MGSeed, long LCGSeed)
    {
        super(MGSeed, LCGSeed);

        Mean = m;
        StandardDeviation = sd;

        double cv, z;
        cv = StandardDeviation / Mean;
        z = cv * cv;
        p = 0.5 * (1.0 - Math.sqrt((z - 1.0) / (z + 1.0)));

        for (int ss = 0; ss < StreamSelect * 1000; ss++)
            uniform();
    }

    /**
     * Return a value from the stream.
     */

    public double getNumber () throws IOException, ArithmeticException
    {
        double z = 0;

        if (uniform() > p)
            z = Mean / (1.0 - p);
        else
            z = Mean / p;

        return -0.5 * z * Math.log(uniform());
    }

    private double Mean;

    private double StandardDeviation;

    private double p;

};
