#include "Table.h"

Table::Table(int size)
{
	elem = new void *[size + 1];
	memset(elem, 0, sizeof(void *) * (size + 1));
	lock = new Lock("Table lock");
	table_size = size + 1;
}

Table::~Table()
{
	delete elem;
	delete lock;
}

int Table::Alloc(void *object)
{
	if (object == NULL)
		return 0;

	int index = 0;
	lock->Acquire();
	for (int i = 1; i < table_size; i++)
		if (elem[i] == NULL)
		{
			index = i;
			break;
		}
	currentThread->Yield();
	if (index != 0)
	{
		elem[index] = object;	
	}
	else
		index = -1;
	lock->Release();
	return index;
}

void* Table::Get(int index)
{
	ASSERT((index >= 0) && (index < table_size));
	return elem[index];
}

void Table::Release(int index)
{
	ASSERT((index >= 0) && (index < table_size));
	elem[index] = NULL;
}
