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
 /*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

/*
 *
 * Simple filtering streambuffer. On overflow and underflow the buffer
 * is handed to a filtering class which may do with it as it sees fit.
 * Code based on example int eh 2.1 / 3.0 iostream manuals
 */


#include <iostream.h>

#ifndef FILTSBUF_H_
#  include <Common/Filtsbuf.h>
#endif

#ifndef zapeof
#  define zapeof(c) ((c)&0377)
#endif


#ifdef NO_NESTED_TYPES
Filterbuf::Filterbuf ( StreamFilter& cl, open_mode m )
#else
Filterbuf::Filterbuf ( StreamFilter& cl, ios::open_mode m )
#endif
                     : streambuf(), 
		       filter(cl),
		       mode(m)
{
}

Filterbuf::~Filterbuf ()
{
}

streambuf* Filterbuf::setbuf ( char* b, int len )
{
    if (base()) return 0;
    
    if (b != 0 && len > sizeof(mbuf))
    {
	/* set up holding area */
	setb((char*) b, ((char*) b) + len);
    }
    else
    {
	/* Use a one character array to achieve "unbuffered" actions. */
	setb(mbuf, mbuf + sizeof(mbuf));
    }
    
    setp(0, 0);				/* put area */
    setg(0, 0, 0);			/* get area */
    return this;
}

int Filterbuf::overflow ( int c )
{
    /* check that output is allowed */
    if (!(mode & ios::out))
	return EOF;
    
    /* make sure there is a holding area */
    if (allocate() == EOF)
	return EOF;
    
    /* verify that there are no characters in get area */
    if (gptr() && gptr() < egptr())
	return EOF;
    
    /* reset get area */
    setg(0, 0, 0);
    
    /* make sure there is a put area */
    if (!pptr()) setp(base(), base());
    
    /* determine how many characters have been inserted but not consumed */
    int w = pptr() - pbase();
    
    /* if c is not EOF it is a character that must also be consumed */
    if (c != EOF)
    {
	/* we always leave space */
	*pptr() = c;
	++w;
    }
    
    /* consume characters */
    int ok = filter.filter(pbase(), w, ios::out);
    
    if (ok)
    {
	/* set up put area. Ensure there is space for one extra character */
	setp(base(), ebuf() - 1);
	return zapeof(c);
    }
    else
    {
	/* indicate error. */
	setp(0, 0);
	return EOF;
    }
}

int Filterbuf::underflow ()
{
    /* check that input is allowed */
    if (!(mode & ios::in))
	return EOF;
    
    /* make sure there is a holding area. */
    if (allocate() == EOF)
	return EOF;
    
    /* if there are characters waiting for output, then send them. */
    if (pptr() && pptr() > pbase())
	overflow(EOF);
    
    /* reset put area */
    setp(0, 0);
    
    /* setup get area */

#ifdef __GNUG__
    int blength = ebuf() - base();
#else
    int blength = blen();
#endif

    if (blength > 1)
	setg(base(), base() + 1, ebuf());
    else
	setg(base(), base(), ebuf());
    
    /* produce characters */
    int ok = filter.filter(base(), blength, ios::in);
    
    if (ok)
	return zapeof(*base());
    else
    {
	setg(0, 0, 0);
	return EOF;
    }
}

int Filterbuf::sync ()
{
    if (gptr() && egptr() > gptr())
	/* no way to return characters to producer */
	return EOF;

    if (pptr() && pptr() > pbase())
    {
	/* flush waiting output */
	int c = overflow(EOF);

	if (c == EOF)
	    return EOF;
    }
    
    /* nothing to do */
    return 0;
}
