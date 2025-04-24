
#include "system.h"
#include "myproduce.h"

int testnum;
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    Thread *t[4];
    t[0] = new Thread("Producer0");
    t[1] = new Thread("Producer1");
    t[2] = new Thread("Producer2");
    t[3] = new Thread("Consumer");

    int i;
    for (i=0; i<3; i++)
    {
        t[i]->Fork(MultiProducer, i);
    }
    t[3]->Fork(FinalConsumer, 3);
    Initialize(20, 3);
}

