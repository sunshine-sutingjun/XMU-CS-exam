
#include "system.h"
#include "mybound.h"

int testnum;
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    Thread *t0 = new Thread("RemoveEven");
    Thread *t1 = new Thread("RemoveOdd");
    Thread *t2 = new Thread("CheckEmpty");

    t0->Fork(RemoveEven, 0);
    t1->Fork(RemoveOdd, 1);
    t2->Fork(CheckEmpty, 2);
    Fill();
}

