#include "dllist.h"
#include "system.h"
#include "utility.h"

int error_type = 0;

DLLElement::DLLElement( void *itemPtr, int sortKey )
{
    next = prev = NULL;
    key = sortKey;
    item = itemPtr;
}


DLList::DLList()
{
    first = last = NULL;
}

DLList::~DLList()
{
    while (Remove(NULL) != NULL)
        ;
}

void DLList::Prepend(void *item)
{
    if (IsEmpty())
    {
        DLLElement *elem = new DLLElement(item, 1);
        first = last = elem;
    }
    else
    {
        DLLElement *elem = new DLLElement(item, first->key - 1);
        first->prev = elem;
        elem->next = first;
        first = elem;
    }
}

void DLList::Append(void *item)
{
    if (IsEmpty())
    {
        DLLElement *elem = new DLLElement(item, 1);
        first = last = elem;
    }
    else
    {
        DLLElement *elem = new DLLElement(item, last->key + 1);
        last->next = elem;
        elem->prev = last;
        last = elem;
    }
}

void *DLList::Remove(int *keyPtr)
{
    if (IsEmpty())
        return NULL;
    if (keyPtr != NULL)
        *keyPtr = first->key;
    DLLElement *head = first;
    if (error_type == 2)
    {
    	DEBUG('p', "error2: switching thread\n");
	currentThread->Yield();
    }
    first = head->next;
    if (first == NULL)
        last = NULL;    //  list is empty
    else
        first->prev = NULL;
    void *item = head->item;
    delete head;
    return item;
}

bool DLList::IsEmpty()
{
    return((first == NULL) && (last == NULL));
}

void DLList::SortedInsert(void *item, int sortKey)
{
    DLLElement *elem = new DLLElement(item, sortKey);
    if (IsEmpty())
    {
        first = last = elem;
    }
    else
    {
        DLLElement *p;
        for (p = first; p != NULL && p->key < sortKey; p = p->next)
            if (error_type == 3)
	    {
		DEBUG('p', "error3: switching thread\n");
		currentThread->Yield();
	    }
	if (error_type == 1)
	{
		DEBUG('p', "error1: switching thread\n");
		currentThread->Yield();
	}
        if (p == NULL)  // last one
        {
            elem->prev = last;
            last->next = e= 1)
	{
		DEBUG('p', "error1: switching thread\n");
		currentThread->Yield();
	}
        if (p == NULL)  // last one
     lem;
            last = elem;    // append to tail
        }
        else
        {
            elem->next = p;
            elem->prev = p->prev;
            if (p->prev != NULL)
                p->prev->next = elem;
            else
                first = elem;   // Prepend to head
            p->prev = elem;
        }
    }
}

void *DLList::SortedRemove(int sortKey)
{
    DLLElement *p;
    for (p = first; p != NULL && p->key <= sortKey; p = p->next)
        if (p->key == sortKey)
        { 
            if (p != first)
            {
                p->prev->next = p->next;
                if (p != last)
                    p->next->prev = p->prev;
                else
                    last = p->prev;
                void *item = p->item;
                delete p;
     