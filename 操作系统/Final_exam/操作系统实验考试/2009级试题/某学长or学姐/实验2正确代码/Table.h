#ifndef TABLE_H
#define TABLE_H

#include "synch.h"
#include "system.h"

class Table
{
public:
	Table(int size);
	~Table();
	int Alloc(void *object);
	void* Get(int index);
	void Release(int index);

private:
	int table_size;
	void **elem;
	Lock *lock;
}; 


#endif
