/*
 * Calendar Queue for Process List
 *     - See Randy Brown, CACM 30(10): 1220-1227 (10/88).
 *     - See also SIMPACK++ code, Paul Fishwick, cis.ufl.edu.
 *
 * Ian.Mathieson@mel.dit.CSIRO.AU, 11 March 1994.
 */

/*
 * Modified slightly for new C++SIM format (release >= 1.5)
 * by M.C.Little@uk.ac.newcastle.
 * 22/3/94
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

#ifndef BOOLEAN_H_
#  include <Common/Boolean.h>
#endif

#ifndef LISTBASE_H_
#  include "ListBase.h"
#endif


const int MAXNBUCKETS = 32*1024;		    // limit on maximum resize
const int QSPACE = MAXNBUCKETS + (MAXNBUCKETS/2);   // total calendar workspace

class Calendar : public ListBase
{
public:
    Calendar ();

    void Insert (Process &, Boolean prior=FALSE);
    Boolean InsertBefore (Process &ToInsert, Process &Before);
    Boolean InsertAfter (Process &ToInsert, Process &After);
    Process *Remove (const Process *p=0);
    const Process* getNext (const Process* = (Process*) 0) const;

    ostream& print (ostream&) const;

private:
    class ProcessNode 
    {
	friend Calendar;
    public:
	ProcessNode(Process* newp); 
	double Time();
    private:
	ProcessNode* nextProcessNode;
	Process* p;
    };

    class TimeNode 
    {
	friend Calendar;
    public:
	TimeNode(ProcessNode* pn);
    private:
	    TimeNode* nextTimeNode;
	ProcessNode* first;
	ProcessNode* last;
	double time;
    };

    TimeNode *calQ[QSPACE];			// array of TimeNode lists 
    TimeNode **calendar;			// current calendar
    int firstSub;
    Boolean resizeEnable;
    int nBuckets;
    int qSize;
    int lastBucket;
    int topThreshold;
    int botThreshold;
    double lastPrio;
    double bucketTop;
    double width;
    void Init(int, int, double, double);
    void DeleteTimeNodeList(TimeNode* head);
    void Resize(int);
    double NewWidth();
    int WhichBucket(double) const;
    double BucketTop(double) const;
};

extern ostream& operator<< (ostream& strm, const Calendar& c);

#include "Calendar.n"

#endif
