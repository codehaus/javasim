/*
 * Copyright (C) 1991-1998,
 *
 * Department of Computing Science,
 * The University,
 * Newcastle upon Tyne,
 * UK.
 *
 * $Id: Uid.h,v 1.1 1998/07/15 16:00:31 nmcl Exp $
 */

#ifndef UID_H_
#define UID_H_ 

/*
 * WARNING:
 * Do NOT move this define
 */

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

/*
 * Due to problems in guaranteeing order of initialisation plus
 * compiler deficiencies in some compilers we define the NIL_UID
 * as a macro rather than a real object.
 */
 
#define NIL_UID (Uid::_arjunaNilUid_())

/*
 *
 * Unique Identifier implementation.
 *
 */

class ostream;

class Uid
{
public:
    /* Constructors & destructor */

    Uid ();
    Uid (const Uid& copyFrom);
    Uid (const char *uidString, Boolean errsOk = TRUE);
    ~Uid ();

    static const Uid& _arjunaNilUid_ ();
    
    /* non-virtual member functions and operators */

    unsigned long hash () const;
    
    Uid& operator= (const Uid&);
    Boolean operator== (const Uid& u) const;
    Boolean operator!= (const Uid& u) const;
    Boolean operator<  (const Uid& u) const;
    Boolean operator>  (const Uid& u) const;

    ostream& print (ostream& strm) const;

    Boolean valid () const;
    char* stringForm () const;
    
private:
    void generateHash ();
    
    static long hostInetAddr();

    /* private state variables */

    long hostAddr;		/* internet address */
    long process;		/* process number */
    long sec;			/* time */
    long other;		        /* random... */

    unsigned long _hash;
    Boolean _valid;
};

#include <Common/Uid.n>

#endif
