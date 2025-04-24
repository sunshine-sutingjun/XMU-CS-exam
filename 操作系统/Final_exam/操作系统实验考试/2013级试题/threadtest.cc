
#include "system.h"
#include "mybuf.h"

int testnum=1;
//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    Thread *t0 = new Thread("Consumer");
    Thread *t1 = new Thread("Producer1");
    Thread *t2 = new Thread("Producer2");

    t0->Fork(BufConsumer, 0);
    t1->Fork(BufProducer, 1);
    t2->Fork(BufProducer, 2);
    BufCreater(10, 2);
}

