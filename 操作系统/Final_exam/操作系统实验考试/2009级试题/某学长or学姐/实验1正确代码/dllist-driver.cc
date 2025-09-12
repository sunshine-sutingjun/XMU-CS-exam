#include <cstdlib>
#include "dllist.h"
#include "system.h"
#include "utility.h"
#include <time.h>

DLList list;
char item[] = "test_item";

void DLLGenerate(int n, int which)
{
    for (int i = 0; i < n; i++)
    {
	int key = rand() % (n * 2);
	DEBUG('p', "Thread %d is inserting key %d\n", which, key);	
        list.SortedInsert(item, key);
    }
}

void DLLRemove(int n, int which)
{
    int key;
    for (int i = 0; i < n; i++)
    {
        list.Remove(&key);
        printf("Thread %d removed key %d\n", which, key);
    }
}
