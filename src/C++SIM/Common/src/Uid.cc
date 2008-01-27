/*
 * Copyright (C) 1991-1998,
 * 
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 * 
 * $Id: Uid.cc,v 1.5 1998/07/28 17:10:34 nmcl Exp $
 */

/*
 * 
 * Unique Identifier implementation. This version uses the internet
 * number of the creating host concatenated with timestamp information.
 */

#include <stddef.h>
#include <unistd.h>
#include <memory.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef WIN32

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>

#else

#include <winsock.h>
#include <time.h>

#endif

#include <string.h>
#include <strstream.h>

#ifndef ERROR_H_
#  include <Common/Error.h>
#endif

#ifndef UID_H_
#  include <Common/Uid.h>
#endif

static const char RCSid[] = "$Id: Uid.cc,v 1.5 1998/07/28 17:10:34 nmcl Exp $";

static int _errorHost_ = -1;

#if defined(sun) || defined(__ultrix)
extern "C"
{
    extern int gethostname (char *, int);
}
#endif

/*
 * The NIL_UID
 */

static Uid *_arjuna_nil_uid = 0;

static long uidsCreated = 0;
static pid_t processId = 0;
static long initTime = 0;

/*
 * We do not use MAXHOSTNAMELEN here as it varies from machine
 * to machine and OS to OS and with binary compatability it might
 * be the case that what works in one place might fail on another
 * This value should be plenty big enough
 */

static const short MAXHOSTLEN = 512;

const Uid& Uid::_arjunaNilUid_ ()
{
    if (_arjuna_nil_uid == 0)
#ifndef WIN32
	_arjuna_nil_uid = new Uid("0:0:0:0");
#else
        _arjuna_nil_uid = new Uid("0_0_0_0");
#endif	
    
    return *_arjuna_nil_uid;
}

/*
 * Public constructors and destructor
 */

/*
 * This is *NOT* thread safe.
 */

Uid::Uid ()
	 : hostAddr(_errorHost_),
	   process(0),
	   sec(0),
	   other(0),
	   _hash(0),
	   _valid(TRUE)
{
    hostAddr = hostInetAddr();		/* calculated only once */

    if (processId == 0)
	processId = ::getpid();
    
    process = processId;

    if (initTime == 0)
	initTime = ::time(0);
    
    sec = initTime;

    if (uidsCreated & 0xf0000000)
    {
	uidsCreated = 0;
	initTime = ::time(0);
    }
    
    other = uidsCreated++;

    generateHash();
}

Uid::Uid (const Uid& copyFrom )
	 : hostAddr(copyFrom.hostAddr),
	   process(copyFrom.process),
	   sec(copyFrom.sec),
	   other(copyFrom.other),
	   _hash(copyFrom._hash),
	   _valid(copyFrom._valid)
{
}

/*
 * Create Uid from string representation. Boolean arg says whether
 * to give up if an error is detected or to simply replace with NIL_UID
 */

Uid::Uid ( const char *uidString, Boolean errsOk )
	 : hostAddr(_errorHost_),
	   process(0),
	   sec(0),
	   other(0),
	   _hash(0),
	   _valid(FALSE)
{
    int slen = (uidString != 0 ? strlen(uidString): 0);
    char *cp = new char[slen+1];
    char *breakp = 0;
    Boolean newFormat = TRUE;
    Boolean uidOk = FALSE;
    char dummy = ' ';

    /* Copy incoming string and split into two parts */

    if (slen > 0)
    {        
	::strcpy(cp, uidString);
#ifndef WIN32	
        breakp = ::strchr(cp, ':');
#else
        breakp = ::strchr(cp, '_');
#endif	
	
        if (breakp)
	{
#ifdef SUPPORT_OLD_UIDS
            *breakp = 0;

	    /* Pull out inet addr from first part */

	    if ((strchr(cp, '.') != 0) &&
		(hostAddr = inet_addr(cp)) != _errorHost_)
	    {
		/* old format uid */
		newFormat = FALSE;
		breakp++;
	    }
	    else
	    {
#ifndef WIN32		
		*breakp = ':';
#else
		*breakp = '_';
#endif		
		breakp = cp;
	    }
#else
	    breakp = cp;
	    
#endif
	    /* Extract fields with istream ops */
	
	    istrstream uid_source(breakp);
	
	    if (newFormat)
	    {
		hex(uid_source);
		uid_source >> hostAddr >> dummy;
	    }
	
	    uid_source >> process >> dummy;
	    uid_source >> sec >> dummy;
	    uid_source >> other;

	    if ((hostAddr != _errorHost_) && (!uid_source.bad()))
		uidOk = TRUE;
	}
    }
    
    if (!uidOk)
    {
	if (errsOk)
	{
	    *this = NIL_UID;
	    _valid = FALSE;
	}
	else
	{
	    error_stream << FATAL << "Uid::Uid string constructor incorrect\n";
	    ::abort();
	}
    }

#ifndef GCC_ARRAY_DELETE_BUG
    delete [] cp;
#else
    delete cp;
#endif

    if (_valid)
	generateHash();    
}

Uid::~Uid ()
{
}

/*
 * Public non-virtual functions and operators
 */

void Uid::generateHash ()
{
    if (_valid)
    {
	char buffer[256];			/* conversion buffer */
	strstream tos(buffer, 256, ios::out);

	tos << *this << ends;

	unsigned long g = 0;
	const char *p = (const char *)buffer;
	size_t len = ::strlen(buffer);

	_hash = 0;
	
	if (buffer)
	{
	    while (len-- > 0)
	    {
		_hash = (_hash << 4) + (*p);
		if (g = _hash & 0xf0000000)
		{
		    _hash = _hash ^ (g >> 24);
		    _hash = _hash ^ g;
		}
		p++;
	    }
	}
    }
    else
	error_stream << WARNING
		     << "Uid::generateHash called for invalid Uid. Will ignore." << endl;
}

ostream& Uid::print ( ostream& strm ) const
{
#ifndef WIN32    
    return strm << hex << hostAddr << ":" << process << ":" << sec << ":" 
		<< other << dec;
#else
    return strm << hex << hostAddr << "_" << process << "_" << sec << "_" 
		<< other << dec;
#endif    
}

Uid& Uid::operator= (const Uid& u)
{
    if (this == &u)
	return *this;

    hostAddr = u.hostAddr;
    process = u.process;
    sec = u.sec;
    other = u.other;
    _hash = u._hash;

    return *this;
}

/*
 * Caller's responsibility to delete this string.
 */

char* Uid::stringForm () const
{
    if (!_valid)
	return NULL;
    else
    {
	char* buffer = ::new char[256];			/* conversion buffer */

	::memset(buffer, '\0', 256);
	
	strstream tos(buffer, 256, ios::out);
	
	tos << *this << ends;

	return buffer;
    }
}

/*
 * Uid comparisons
 */

Boolean Uid::operator== ( const Uid& u ) const
{
    return ((other == u.other) &&
	    (sec == u.sec) &&
	    (process == u.process) &&
	    (hostAddr == u.hostAddr));
}

Boolean Uid::operator!= ( const Uid& u ) const
{
    return ((other != u.other) ||
	    (sec != u.sec) ||
	    (process != u.process) ||
	    (hostAddr != u.hostAddr));
}

Boolean Uid::operator< ( const Uid& u ) const
{
    if (hostAddr < u.hostAddr)
	return TRUE;
    else if (hostAddr == u.hostAddr)
    {
	if (process < u.process)
	    return TRUE;
	else if (process == u.process)
	{
	    if (sec < u.sec)
		return TRUE;
	    else if ((sec == u.sec) && (other < u.other))
		return TRUE;
	}
    }
    return FALSE;
}

Boolean Uid::operator> ( const Uid& u ) const
{
    if (hostAddr > u.hostAddr)
	return TRUE;
    else if (hostAddr == u.hostAddr)
    {
	if (process > u.process)
	    return TRUE;
	else if (process == u.process)
	{
	    if (sec > u.sec)
		return TRUE;
	    else if ((sec == u.sec) && (other > u.other))
		return TRUE;
	}
    }
    return FALSE;
}

long Uid::hostInetAddr ()
{
    static long myAddr = 0;
    static char hostname[MAXHOSTLEN];

    if (myAddr == 0)
    {
	struct hostent *h = 0;
	
	::memset(hostname, 0, MAXHOSTLEN);
	::gethostname(hostname, MAXHOSTLEN);
	h = ::gethostbyname(hostname);
	::memcpy(&myAddr, h->h_addr, h->h_length);
    }

    return myAddr;
}

#ifdef NO_INLINES
#  define UID_CC_
#  include <Common/Uid.n>
#  undef UID_CC_
#endif
