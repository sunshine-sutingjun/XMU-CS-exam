// threadtest.cc
//      Simple test case for the examination to illustratethe inner
//	workings of the thread system.
//----------------------------------------------------------------------

#include "copyright.h"
#include "system.h"
#include "synch.h"
#include "BoundedBuffer.h"
// Add a header file here which are required.

#define MAXBYTES	1024
#define	BUFSIZE		4
BoundedBuffer buf(BUFSIZE);					 
// testnum is set in main.cc
int testnum = 1;
//----------------------------------------------------------------------
// Consumer
//      Read all of bytes in buf written by the two Producers to data,  
//	then print tnem as a string.
//----------------------------------------------------------------------
void
Consumer(int which)
{
	char data[MAXBYTES];
       // int i=0;
        while(true)
        { buf.Read((void *)data,buf.Size());
         if(buf.Getcount()==0)
         printf("Output: %s\n",data);
        }  
          
        
//----------------------------------------------------------------------
// Add proper program statements here to have the consumer run
// accordingly.
//----------------------------------------------------------------------
	printf("Output: %s\n", data);
}

//----------------------------------------------------------------------
// Producer
//      Write buf.Size() number of "aa" or "bb" into buf, whichever are
//	written	is determined by "which". If your class dose not have
//	member function buf.Size(), which returns the size of buf, add it
//	by yourself.
//-----------------------------------------------------------------------
void
Producer(int which)
{
        int i;
        char *s;

	if(which == 1)
		s = "aa";
	else
		s = "bb";
	
	for(i = 0; i < buf.Size(); i++) {
		buf.Write((void *)s, 2);
                currentThread->Yield();
	}
}		

//----------------------------------------------------------------------
// ThreadTest
//      Create two producer threads and run itself as a consumer.
//----------------------------------------------------------------------
void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t1 = new Thread("forked thread1");
    Thread *t2 = new Thread("forked thread2");

    t1->Fork(Producer, 1);
    t2->Fork(Producer, 2);
    Consumer(1);
}
