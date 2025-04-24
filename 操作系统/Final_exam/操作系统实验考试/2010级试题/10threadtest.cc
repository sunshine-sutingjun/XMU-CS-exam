//---------------------------------------------------------------------
// threadtest.cc
//      Simple test case for the examination to illustratethe inner
//	workings of the thread system.
//
//6----------------------------------------------------------------------

#include "copyright.h"
#include "system.h"
#include "dllist.h"  // Your double list header file
#include "synch.h"
//12 Add a header file here which are required.

DLList *list = new DLList(); // the shared double list
static int key[10] = {9,6,5,0,8,1,3,2,4,7}; // ten items that will be
					    // inserted into the list

// Define a semaphore that synchronizes the Producer and the Comsumer.

//20 testnum is set in main.cc
int testnum = 1;
Semaphore *s=new Semaphore("aaa",0);  //-22-----------------!!!!!!!
//----------------------------------------------------------------------
// Consumer
//      Remove and print 10 items in the key order from the shared
//	double list.
//	The items are inserted by producers.
//------------28----------------------------------------------------------

void
Consumer(int which)
{
        int *item;
        int i;
        for(i = 0; i< 10; i++) {
                item = (int *)list->SortedRemove(i);
                while(item == NULL) {
                   s->P();  //!!!!!!!!!!!!!!!!
                   item=(int*)list->SortedRemove(i); //!!!!!!!


//----------------------------------------------------------------------
// Reaching here means the item with key k is not in the list right now,
// and consumer has to be waiting until the item has been inserted by
// producers.
//
// Write proper program statements whitin this while statement to have
// consumer run accordingly. Do not use Yield, instead use a semaphore
// to synchronize the the Producer and the Comsumer.
//----------------------------------------------------------------------
                }
                printf("%d ", *item);
        }
        printf("\n"); // Ending output with newline
}

//----------------------------------------------------------------------
// Producer
//      Sorted insert 10 items into the double list. This thread yields
//	after every inserting a item to let the Comsumer run. cs8.xmu.edu.cncs8.xmu.edu.cn
//-----------------------------------------------------------------------

int k;
void
Producer(int which)
{
        int n;

        for(n = 0; n < 10; n++) {
                k = key[n];
                list->SortedInsert(&key[n], k);
                currentThread->Yield();  //!!!!!!!!!!!!!!!!!!!!!!
                s->V();  //!!!!!!!!!!!!!!!!!!!!!
//----------------------------------------------------------------------
// Write proper program statement here whitin this for statement to have
// Producer run accordingly.
//-----------------------------------------------------------------------
        }
}


//----------------------------------------------------------------------
// ThreadTest
//      Create a producer thread and run itself as a consumer.
//----------------------------------------------------------------------

void
ThreadTest()
{
    DEBUG('t', "Entering ThreadTest1");
    Thread *t = new Thread("forked producer");
    t->Fork(Producer, 1);
    Consumer(1);
}

