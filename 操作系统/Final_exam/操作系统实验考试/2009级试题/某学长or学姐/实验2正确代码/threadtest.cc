// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include <cstdlib>
#include "copyright.h"
#include "system.h"
#include "dllist.h"
#include "Table.h"
#include "BoundedBuffer.h"
#include "synch.h"

// testnum is set in main.cc
int testnum = 1;
int threadnum = 2;
int listsize = 5;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
       	currentThread->Yield();
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1);
    SimpleThread(0);
}

void GenerateList(int which)
{
	DLLGenerate(listsize, which);
	//DLLRemove(listsize, which);
}

void ThreadTest2()
{
	DEBUG('t', "Entering ThreadTest2");
	for (int i = 1; i < threadnum; i++)
	{
		Thread *t = new Thread("forked thread");

		t->Fork(GenerateList, i);
	}
	DLLRemove(listsize, 0);
	//GenerateList(0);
}

Lock lock("lock test");

void Message(int which)
{
	lock.Acquire();
	printf("Thread %d: Message1\n", which);
	currentThread->Yield();
	printf("Thread %d: Message2\n", which);
	lock.Release();
}

void ThreadTest3()
{
	DEBUG('t', "Entering ThreadTest3");
	for (int i = 1; i < threadnum; i++)
	{
		Thread *t = new Thread("forked thread");
		t->Fork(Message, i);
	}
	Message(0);
}

DLList dltest;
Condition isempty("contest");
Lock c_lock("locktest");

void Writer(int x)
{
	for (int i = 0; i < 5; i++)
	{
		c_lock.Acquire();
		printf("Write: %d\n", i);
		dltest.Append((void *) i);
		isempty.Signal(&c_lock);
		currentThread->Yield();
		c_lock.Release();
	}
}

void ThreadTest4()
{
	DEBUG('t', "Entering ThreadTest4");
	Thread *t = new Thread("Writer");
	c_lock.Acquire();
	t->Fork(Writer, 0);
	
	for (int i = 0; i < 5; i++)
	{
		int key;
		while (dltest.IsEmpty())
			isempty.Wait(&c_lock);
		int x = (int) dltest.Remove(&key);
		printf("Read: %d\n", x);
	}
	c_lock.Release();
}

Table table(10);

void TableThread(int which)
{
	int idx[3], i;	
	for (i = 0; i < 3; i++)
	{
		void *obj = (void *)(rand() % 100 + 1);
		DEBUG('p', "Thread %d: inserting object %d\n", which, (int) obj);
		idx[i] = table.Alloc(obj);
		DEBUG('p', "Thread %d: index = %d\n", which, idx[i]);
		currentThread->Yield();
	}
	for (i = 0; i < 3; i++)
		DEBUG('p', "Thread %d: table[%d] == %d\n", which, idx[i], (int) table.Get(idx[i]));
	for (i = 0; i < 3; i++)
	{
		DEBUG('p', "Thread %d: Releasing table[%d]\n", which, idx[i]);
		table.Release(idx[i]);
		DEBUG('p', "Thread %d: Finish!\n", which);
		currentThread->Yield();
	}
}

void TableTest()
{
	Thread *t = new Thread("forked thread");
	t->Fork(TableThread, 1);
	TableThread(0);
}

BoundedBuffer bbuff(3);

void bbuffThread(int x)
{
	char buf[2] = "A";
	for (int i = 0; i < 20; i++)
	{
		printf("Producer: write %s\n", buf);
		bbuff.Write(buf, 1);
		++buf[0];
	}
}

void BoundedBufferTest()
{
	Thread *t = new Thread("forked thread");
	t->Fork(bbuffThread, 1);
	
	for (int i = 0; i < 10; i++)
	{
		char buf[3] = { 0 };
		bbuff.Read(buf, 2);
		printf("Consumer: read %s\n", buf);
	}
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    case 2:
	ThreadTest2();
	break;
    case 3:
	ThreadTest3();
	break;
    case 4:
    	ThreadTest4();
	break;
    case 5:
	TableTest();
	break;
    case 6:
	BoundedBufferTest();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

