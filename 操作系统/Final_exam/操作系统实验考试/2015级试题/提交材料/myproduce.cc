#include "myproduce.h"
#include "stdlib.h"
#include "system.h"
// Add a header file if needed
#include "synch.h"


//-----------------------------------------------------------------
// Semaphores to be used for mutual exclusion and synchronization
//-----------------------------------------------------------------
Semaphore *pause[3]; 
Semaphore *mutex = new Semaphore("mutex", 1) /* Add proper initialization HERE */ ;
Semaphore *start = new Semaphore("start", 0);
Semaphore *delay = new Semaphore("delay", 0) /* Add proper initialization HERE */ ;

int * pbuf = NULL; // pointer to shared array 
int pos = 0; // initial index position of pbuf


//-----------------------------------------------------------------
// Initialize(bufsize, totalprod);
//     bufsize   : size of buffer
//     totalprod : total number of producers
//
//     Allocate memory space for pbuf and do some initialization
// needed.
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void Initialize(int bufsize, int totalprod)
{	
    int i;
    for (i=0; i<totalprod; i++)
    {
        pause[i] = new Semaphore("pause", 0); 
    }
    // Add one or more proper statements HERE.
    // Do nothing?
    mutex->P();
    currentThread->Yield();

    pbuf = (int*)calloc(bufsize, sizeof(int));
    if (pbuf == NULL)
    {
        printf("failed to allocate the buffer!");
        return;
    }
    else
    {
    // Add one or more proper statements HERE.
        // Emit start event
        for(i = 0; i < 3; i++) start->V();  // Signal all 3 producers to start
        pause[0]->V();  // Unpause producer0
        // printf("[ Initialize ] Unpausing producer0\n");
        mutex->V();
    }
    
}

//-----------------------------------------------------------------
// MultiProducer(which) 
//     which : thread id
//
//     Fill entries into the buffer as required.
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void MultiProducer(int which)
{
    start->P();

    // Add one or more proper statements HERE.
    // Do nothing
    int i;
    for (i=0; i<3; i++)
    {
    // Add one or more proper statements HERE.
        // printf("[ Producer%d ] Pausing\n", which);
        pause[which]->P();  // Wait for previous producer to signal
        // printf("[ Producer%d ] Unpaused. Inserting %d\n", which, i * 3 + which + 1);
        mutex->P();  // Acquire lock (may be unnecessary)
        pos++;
        pbuf[pos-1]=i*3+which+1;
    // Add one or more proper statements HERE.
        // printf("[ Producer%d ] Unpausing producer%d\n", which, (which + 1) % 3);
        pause[(which + 1) % 3]->V();  // Signal next producer
        mutex->V();  // Release lock
        // It's OK if the value of `pos` was changed after lock released. `delay` event could emit multiple times but it's waited only once
        if (pos == 9)
        {
            delay->V();
        }
        else
        {
    // Add one or more proper statements HERE.
            // Do nothing?
            currentThread->Yield();
        }
    } 
}

//-----------------------------------------------------------------
// FinalConsumer(which)
//     which : thread id
//
//     Remove all numbers from the buffer.  
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void FinalConsumer(int which)
{
    // Add one or more proper statements HERE.
    // Wait for `delay` event
    // printf("[ FinalConsumer ] Waiting for `delay` event.\n");
    delay->P();  // Once `delay` event emit, no one but `FinalConsumer` would access `pbuf`
    mutex->P();  // Acquire lock (may be unnecessary)
    while (pos>0)
    {
        printf("%d ", pbuf[pos-1]);
        pbuf[pos-1] = 0;
        pos--;
    }
    printf("\n");
    // Add one or more proper statements HERE.
    // Clean up?
    mutex->V();  // Release lock
    delete []pbuf;
    pbuf = NULL;
    for(int i = 0; i < 3; i++) delete pause[i];
}
