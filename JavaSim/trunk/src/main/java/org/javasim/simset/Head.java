/*
 * Copyright 1990-2010, Mark Little, University of Newcastle upon Tyne
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
 * (C) 1990-2010,
 */

package org.javasim.simset;

/*
 * This class essentially defines the linked list manager used by the SIMSET
 * class in SIMULA.
 */

// Thanks to Jim Bean for converting the C++SIM classes

public class Head  {

    public Head () {
        this.first = null;
        this.last = null;
    }

    synchronized public Link first () {return first;};

    synchronized public Link last  () {return last;};

    public void addFirst (Link element) {

        if (element == null)       // nothing to add
            return;

        if (element.inList())     // if in another list
            element.out();        // pull it out.
        
        if (first == null) {      // Queue presently empty
        
            first = element;
            last = element;
            element.theList = this;

        } else {
            element.precede(first);
            first = element;
        }
    };

    public void addLast (Link element) {

        if (element == null)       // nothing to add
            return;
        
        if (element.inList())     // if in another list
            element.out();        // pull it out.

        if (last == null) {      // Queue presently empty
        
            first = element;
            last = element;
            element.theList = this;

        } else {
            element.follow(last);
            last = element;
        }
    };

    synchronized public long cardinal () {
        long numberOfElements = 0;
        Link tempPtr = first;
    
        while (tempPtr != null) {

            numberOfElements++;
            tempPtr = tempPtr.suc();
        }
    
        return numberOfElements;
    };

    synchronized public boolean empty () {return cardinal() == 0;};

    synchronized public void clear () {
        Link tempPtr = first, marker = null;
    
        while (tempPtr != null) {

            marker = tempPtr;
            tempPtr = tempPtr.suc();
            marker = null;
        }

        first = null;
        last  = null;
    };

    protected Link first;
    protected Link last;

}