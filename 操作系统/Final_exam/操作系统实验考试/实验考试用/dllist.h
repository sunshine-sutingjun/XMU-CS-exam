

#include "copyright.h"
#include "utility.h"


class DLListElement {
   public:
     DLListElement(void *itemPtr, int sortKey);	// initialize a list element

     DLListElement *next;		// next element on list,
				// NULL if this is the last
     DLListElement *prev;    // previous element on list
                             // NULL if this is the first
     int key;		    	// priority, for a sorted list
     void *item; 	    	// pointer to item on the list
};


class DLList {
  public:
    DLList();			// initialize the list
    ~DLList();			// de-allocate the list

    void Prepend(void *item); 	// add to head of list (set key = min_key-1)
    void Append(void *item); 	// add to tail of list (set key = max_key-1)
    void *Remove(int *keyPtr); 	 	// remove from head of list
                                    // set *keyPtr to key of the removed item
                                    // return item (or NULL if list is empty)

    bool IsEmpty();		// is the list empty?


    // Routines to put/get items on/off list in order (sorted by key)
    void SortedInsert(void *item, int sortKey);	// Put item into list
    void *SortedRemove(int sortKey); 	  	// Remove first item with key==sortKey
                                            // return NULL if no such item exists

    void Print();

  private:
    DLListElement *first;  	// Head of the list, NULL if list is empty
    DLListElement *last;		// Last element of list,NULL if empty
};

