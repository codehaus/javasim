/*
 * Copyright (C) 1994
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 */

#ifndef FILTSBUF_H_
#define FILTSBUF_H_

/* Unfortunately we need iostream.h for the definition of ios::open_mode */

#include <iostream.h>

/*
 * A base class only. The filtering streambuffer uses an instance of a
 * class derived from this to perform the actual filtering of the buffer
 */

class StreamFilter
{
public:
#ifndef NO_NESTED_TYPES
    virtual int filter (const char *, int, ios::open_mode) = 0;
#else
    virtual int filter (const char *, int, open_mode) = 0;
#endif
};

/*
 * A filtering streambuf - constructed following the example in the 2.1
 * release documentation
 */

class Filterbuf : public streambuf
{
public:

#ifndef NO_NESTED_TYPES
    Filterbuf (StreamFilter&, ios::open_mode);
#else
    Filterbuf (StreamFilter&, open_mode);
#endif
    
    ~Filterbuf ();

protected:
    int overflow (int);
    int underflow ();
    int sync ();
    streambuf* setbuf (char*, int);
private:
    StreamFilter& filter;
#ifdef NO_NESTED_TYPES
    open_mode	mode;
#else
    ios::open_mode	mode;
#endif
    char mbuf[1];
};

#endif