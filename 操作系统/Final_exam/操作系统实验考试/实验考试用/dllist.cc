
#include "copyright.h"
#include "dllist.h"
#include "thread.h"
extern Thread *currentThread;
extern int errortype;



DLListElement::DLListElement(void *itemPtr, int sortKey)
{
     item = itemPtr;
     key = sortKey;
     next = NULL;	// assume we'll put it at the end of the list
     prev = NULL;
}



DLList::DLList()
{
    first = last = NULL;
}


DLList::~DLList()
{
    while (Remove(NULL) != NULL)
	;	 // delete all the list elements
}



void
DLList::Append(void *item)
{
    

    if (IsEmpty()) {		// list is empty
	DLListElement *element = new DLListElement(item, 0);
	first = element;
	last = element;
    }
    else {			// else put it after last
	DLListElement *element = new DLListElement(item,last->key+1);
	element->next=NULL;
	element->prev=last;
	last->next = element;
	last = element;
    }
}


void
DLList::Prepend(void *item)
{
    

    if (IsEmpty()) 
	{		// list is empty
	DLListElement *element = new DLListElement(item, 0);
	first = element;
	last = element;
    }
    else 
	{			// else put it before first
	DLListElement *element= new DLListElement(item,(first->key-1));
	element->next=first;
	element->prev=NULL;
	first->prev=element;
	first = element;
    }
}


void * DLList::Remove(int *keyPtr)
{
	if(IsEmpty())
	{
		keyPtr=NULL;
		return NULL;
	}
	else
	{
		*keyPtr = first->key;
		return SortedRemove(*keyPtr);
	}
}



bool
DLList::IsEmpty()
{
    if (first == NULL)
    {
        ASSERT(first==last);
        return TRUE;
    }
    else
	return FALSE;
}



void
DLList::SortedInsert(void *item, int sortKey)
{
    DLListElement *element = new DLListElement(item, sortKey);
    DLListElement *ptr;		// keep track

    if (IsEmpty()) {	// if list is empty, put
        first = element;
        last = element;
    }
    else if (sortKey < first->key) {
		// item goes on front of list
	element->prev = NULL;
	element->next = first;
	first->prev=element;
	first = element;
    }
    else {		// look for first elt in list bigger than item
        for (ptr = first; ptr->next != NULL; ptr = ptr->next) {
            if (sortKey < ptr->next->key) {
		element->next = ptr->next;
       /* if(errortype==4)
        {
	    printf("now key=%d,now thread=\n",sortKey);
            printf("An yield is occur\n");
            currentThread->Yield();
        }*/
		element->prev=ptr;
		ptr->next->prev=element;
        ptr->next = element;
        //Print();
        //currentThread->Yield();
		return;
	    }
	}
	element->next=NULL;
	element->prev=last;
	last->next = element;		// item goes at end of list
	last = element;
    }
  //  Print();
    //currentThread->Yield();
}




void* DLList::SortedRemove(int sortKey)
{
	if(IsEmpty())
		return NULL;
		DLListElement * p=first;
		while((p!=NULL)&&(p->key!=sortKey))
		{
			//head2=head1;
			p=p->next;
		}
		if(p==NULL)
			return NULL;
		else if(p==first)
		{
			DLListElement *rm=first;
			void *thing=first->item;
			first=first->next;
	        if(first==NULL)
			{
				first=last=NULL;
				delete rm;
				return thing;
			}
			else
			{
				first->prev=NULL;
				delete rm;
				return thing;
			}
		}
		else
		{
			void *thing=p->item;
			DLListElement * q=p->prev;
			q->next=p->next;
			if(p->next!=NULL)
				p->next->prev=q;
			else last=q;
			delete p;
			return thing;
		}

}

void DLList::Print()
{
    DLListElement *ptr;		// keep track
    printf("Items in the dllist are:");
    if (IsEmpty())
        printf("NULL ");
    else
    {
        for (ptr = first; ptr != NULL; ptr = ptr->next)
        {
            printf("%d ",ptr->key);
        }
    }
  //  printf("\n");

}

