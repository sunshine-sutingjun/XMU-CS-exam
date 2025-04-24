#include "mybuf.h"
#include "stdlib.h"
#include "system.h"
#include "synch.h"

// Add a header file if needed

//-----------------------------------------------------------------
// Semaphores to be used for mutual exclusion and synchronization
//-----------------------------------------------------------------
Semaphore *mutex = new Semaphore("mutex", 1);
Semaphore *start = new Semaphore("start", 0);
Semaphore *delay = new Semaphore("delay", 0); /* Add proper initialization HERE */ ; 

int * pbuf = NULL; /* pointer to shared array */
int pos = 0;       /* initial index position of pbuf */

//-----------------------------------------------------------------
// BufCreater
//      Allocate memory space for pbuf, it must complete execution 
// before BufProduer starts
//-----------------------------------------------------------------


int BufCreater(int bufsize, int totalproducers)
{
    currentThread->Yield();

    pbuf = (int*)calloc(bufsize, sizeof(int));
    if (pbuf == NULL)
    {
        printf("failed to create the buffer!");
        return -1;
    }
    else
    {
        int i;
        for (i=0; i<totalproducers; i++)
        {
		start->V();
		
// Add one or more statements HERE.
        }
        return 0;
    }
}

//-----------------------------------------------------------------
// BufProducer
//      Insert items into pbuf. You shall add approriate thread 
// switch somewhere so that the insertion happens as we require
//-----------------------------------------------------------------
void BufProducer(int which)
{
    start->P();

    int i;
    for (i=0; i<5; i++)
    {   
	mutex->P();	
// Add one or more proper statements HERE.
        pos++;
        if (which%2== 1)
            currentThread->Yield();
        pbuf[pos-1]=i*2+which;
	mutex->V();
	currentThread->Yield();
	if(pos >= 10)
		delay->V();
// Add one or more proper statements HERE.
	
    }
}

//-----------------------------------------------------------------
// BufConsumer
//      Remove items from pbuf by the reverse order of insertion.
// BufConsumer should not proceed until BufProducer completes.
//-----------------------------------------------------------------
void BufConsumer(int which)
{
    delay->P();
    while(pos>0)
    {
        printf("%d ", pbuf[pos-1]);
        pbuf[pos-1]=0;
        pos--;
    }
    printf("\n");
}
