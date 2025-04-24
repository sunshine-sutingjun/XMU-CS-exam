#ifndef BOUNDEDBUFFER_H
#define BOUNDEDBUFFER_H

#include <cstdlib>
#include "system.h"
#include "synch.h"

class BoundedBuffer
{
public:
	BoundedBuffer(int maxsize);
	~BoundedBuffer();

	void  Read(void *data, int size);
	void Write(void *data, int size);

private:
	int buffer_size;
	int read_pos;
	int write_pos;
	int count;
	Condition *cond;
	Lock *notfull;
	Lock *notempty;
	char *buffer;

};

#endif
