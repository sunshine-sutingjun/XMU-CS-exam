// threadtest.cc 
//	Simple test case for the OS examination.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
//----------------------------------------------------------------------
#include "copyright.h"
#include "system.h"
#include "dllist.h"  // Your double list header file
#include "synch.h"

Semaphore *lock = new Semaphore("List Lock",1); // use to mutex
Semaphore *testlock1 = new Semaphore("List lock 1",1);
Semaphore *testlock2 = new Semaphore("List lock 2",0);
DLList *list = new DLList();
static int key[11] = {0,1,2,3,4,5,6,7,8,9,10};

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// Prlist
// 	Remove one item from double list and print it. thread0 remove
//	and print the item with even key while thread1 the item
//	with odds key.
//----------------------------------------------------------------------

void
PrList(int n, int which)
{
	int value;
	int k;

	k = 2*n-which;
	value = *((int *)list->SortedRemove(k));
	printf("%d ", value);
	if(k == 10)
		printf("\n"); // Ending output with newline
}

//----------------------------------------------------------------------
// SimpleThread
// 	Sorted insert 5 items into a double list according to "which", 
//	then remove the items and print them. There are two threads running
//	this function alternately, which print cooperratively to 
//	produce output: 1 2 3 4 5 6 7 8 9 10
//	
//	"which" is a number identifying the thread, the thread with 0
//	of "which" inserts items with even key and the thread with 1
//	inserts items with odds key.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
	int n,idx;
        for(n=1; n<=5; ++n){ // Sorted insert 5 items according to "which"
		idx = 2*n-which;
		lock->P();
          	list->SortedInsert(&key[idx], key[idx]);
		lock->V();
          	currentThread->Yield();
        }
        for(n=1; n<=5; ++n){ // Remove previously inserted items and print them 		
		if(which==0)
			testlock2->P();
			else testlock1->P();
		lock->P();
        	PrList(n, which);
		lock->V();
		if(which==0)
			testlock1->V();
			else
				testlock2->V();
	}
}


//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1);
    SimpleThread(0);
}
