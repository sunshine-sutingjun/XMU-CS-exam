#include "mybound.h"
#include "stdlib.h"
#include "system.h"

#include "synch.h"
// Add a header file if needed

#define NUM     10
#define SIZE    3

//-----------------------------------------------------------------
// Semaphores to be used for mutual exclusion and synchronization
//-----------------------------------------------------------------
Semaphore *empty = new Semaphore("empty",1) /* Add proper initialization HERE */ ;
Semaphore *lock  = new Semaphore("lock", 1);
Semaphore *full = new Semaphore("full", 0);
Semaphore *cont = new Semaphore("cont",0); /* Add proper initialization HERE */ ;

int src[NUM] = {1, 2, 3, 5, 5, 5, 6, 7, 8, 9}; /* source of items */
int buf[SIZE] = {-1, -1, -1};     /* a bounded buffer */
int curp = 0;       /* initial index position in buf */
int curn = NUM;     /* number of items to process */
int curs = 0;	    /* current number of items in buf */

//-----------------------------------------------------------------
// Fill
//     Fill a bounded buf with src's items by their initial order. 
//
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void Fill()
{
    int n = 0;
    
    while (n != NUM)
    {
	currentThread->Yield();
        empty->P();

	lock->P();
	// Add one or more proper statements HERE.
	currentThread->Yield();
        while (curp != SIZE && n != NUM)
        {
            buf[curp] = src[n];
            curp++;
	    curs++;
            n++;
        }
        if (curp == SIZE)
        {
            curp = 0;
	    // Add one or more proper statements HERE.

	    lock->V();
            full->V();
        }
    }

    lock->V();
    full->V();
    // Add one or more proper statements HERE.
}

//-----------------------------------------------------------------
// RemoveOdd 
//     Remove all odd numbers from the buf.  
//
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void RemoveOdd(int which)
{
    while (1)
    {
        // Add one or more proper statements HERE.
	full->P();
	lock->P();

        int i;
        for (i=0; i<SIZE; i++)
        {
            if (buf[i] % 2 == 1)
            {
                printf("%d-%d\n", which, buf[i]);
                buf[i] = 0;
		currentThread->Yield();
                curs--;
                curn--;
            }
        }
        // Add one or more proper statements HERE.
        lock->V();
	if (curs ==0)
	   currentThread->Yield();

        if (curs != 0)
        {
            // Add one or more proper statements HERE.
	    cont->V();
        }
        
        if (curn == 0)
            break;
    }
}

//-----------------------------------------------------------------
// RemoveEven
//     Remove all even numbers from the buf.  
//
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void RemoveEven(int which)
{
    while (1)
    {
	//full->P();
        cont->P();
	lock->P();

        // Add one or more proper statements HERE.
        int i;
        for (i=0; i<SIZE; i++)
        {
            if (buf[i]!=0/* Add one or more proper statements HERE. */)
            {
                printf("%d-%d\n", which, buf[i]);
                buf[i] = 0;
		currentThread->Yield();	
                curs--;
                curn--;
            }
        }
        // Add one or more proper statements HERE.

	lock->V();
	currentThread->Yield();

        if (curn == 0)
            break;
    }
}

//-----------------------------------------------------------------
// CheckEmpty 
//     Check repeatedly whether the buf is empty or not. 
//
//     See the testpaper for detailed description. You shall assume
// thread switch may take place right after any statement within 
// this function, although some Yields have been used here for 
// limited test. 
//-----------------------------------------------------------------
void CheckEmpty(int which)
{
    while (1)
    {

	lock->P();
        // Add one or more proper statements HERE.
        int i, res=1; // res==1 means the buf is empty
        for (i=0; i<SIZE; i++)
        {
            if (buf[i] != 0)
            {
                res=0;
                break;
            }
        }
	currentThread->Yield();
        if (res == 1)
        {
	    empty->V();
            // Add one or more proper statements HERE.
        }
        
	lock->V();
        // Add one or more proper statements HERE.
        
	currentThread->Yield();        
        if (curn == 0)
            break;
    }
}

