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


DLList *list = new DLList();
static int key[10] = {1,2,3,4,5,6,7,8,9,0};

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// Prlist
// 	Remove one item from double list and print it. thread0 remove
//	and print the item with even key while thread1 the item
//	with odds key.
//----------------------------------------------------------------------

void
Consumer(int which)
{
	int *item;
	int k;
	for(k = 0; k< 10; k++){
        item = (int *)list->SortedRemove(k);
        while(item == NULL){
            currentThread->Yield();     //原来没有，考试时加的
            item = (int *)list->SortedRemove(k);    //原来没有，考试时加的
        }
        printf("%d ", *item);
	}
	printf("\n"); // Ending output with newline
}

void
Producer(int which)
{
    int k;
    int n;
    for(n = 0; n < 5; n++){
        k = key[2*n+which];
        list->SortedInsert(&key[2*n+which],k);
        currentThread->Yield();
    }
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
    t->Fork(Producer,0);
    t = new Thread("forked thread");
    t->Fork(Producer,1);
    Consumer(2);
}
