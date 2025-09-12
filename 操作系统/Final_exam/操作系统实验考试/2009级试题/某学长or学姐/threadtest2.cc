// threadtest.cc 
//	Simple test case for the examination.
//
//	Create two different threads, and have context switch between them
//	by calling Thread::Yield to illustratethe inner workings of the
//	thread system.
//----------------------------------------------------------------------

#include "copyright.h"
#include "system.h"
#include "dllist.h"  // Your double list header file
#include "synch.h"

DLList *list = new DLList(); // allocate a double list
static int key[10] = {8,2,1,5,6,9,7,3,4,10}; // 10 randomly saved keys
Semaphore *lock = new Semaphore("lock", 1);
// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// Prlist
// 	Remove the items from double list and print them. The items are
//	removed in the key order "1,2,3,4,5,6,7,8,9,10" and also print
//	them in that order.
//
//	"which" is a number identifying the thread.
//----------------------------------------------------------------------

void
PrList(int which)
{
	int *item;
	
	for(int k = 1; k <= 10; k++){
		
		item = (int *)list->SortedRemove(k);
		while(item == NULL) {
//----------------------------------------------------------------------
//	If we are here means the item with key k is not in the
//	double list at present. What the proper action should we do?
//	Add some relative statements here to make the program
//	run accordingly.
//----------------------------------------------------------------------
			
			currentThread->Yield();
			item = (int *)list->SortedRemove(k);
			currentThread->Yield();
		};
		printf("%d ", *item); // print the item just removed
	}
	printf("\n"); // Ending output with newline
}

//----------------------------------------------------------------------
// SimpleThread
// 	Sorted insert 10 items into a double list according to the
//	order in which the keys are saved in array key[]. This thread
//	has some context switchs during it's running to allow the
//	other thread gains CPU.
//
//	"which" is a number identifying the thread.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
	int k;
	
        for(int n = 0; n < 10; n++) {
		k = key[n];
          	currentThread->Yield();
          	list->SortedInsert(&key[n], k);
          	currentThread->Yield();
        }
}


//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call PrList, and then calling SimpleThread itself.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(PrList, 1);
    SimpleThread(0);
}

