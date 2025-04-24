#include "myproduce.h"
#include "stdlib.h"
#include "system.h"
// Add a header file if needed


//-----------------------------------------------------------------
// Semaphores to be used for mutual exclusion and synchronization
//-----------------------------------------------------------------
Semaphore *pause[3]; 
Semaphore *mutex /* Add proper initialization HERE */ ;
Semaphore *start = new Semaphore("start", 0);
Semaphore *delay /* Add proper initialization HERE */ ;

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

    int i;
    for (i=0; i<3; i++)
    {
    // Add one or more proper statements HERE.
        pos++;
        pbuf[pos-1]=i*3+which+1;
    // Add one or more proper statements HERE.
        if (pos == 9)
        {
            delay->V();
        }
        else
        {
    // Add one or more proper statements HERE.
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
    while (pos>0)
    {
        printf("%d ", pbuf[pos-1]);
        pbuf[pos-1] = 0;
        pos--;
    }
    printf("\n");
    // Add one or more proper statements HERE.
}