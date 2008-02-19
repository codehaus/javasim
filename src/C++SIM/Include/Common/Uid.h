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
