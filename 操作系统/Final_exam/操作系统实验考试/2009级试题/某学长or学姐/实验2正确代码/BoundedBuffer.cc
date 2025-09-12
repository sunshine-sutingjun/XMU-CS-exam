#include "BoundedBuffer.h"

BoundedBuffer::BoundedBuffer(int maxsize)
{
	buffer_size = maxsize;
	buffer = (char *) malloc(maxsize);
	cond = new Condition("cond");
	notfull = new Lock("notfull");
	notempty = new Lock("notempty");
	read_pos = write_pos = 0;
	count = 0;
}

BoundedBuffer::~BoundedBuffer()
{
	delete notfull;
	delete notempty;
	delete cond;
	free(buffer);
}

void BoundedBuffer::Read(void *data, int size)
{
	char *out_buf = (char *) data;
	while (size--)
	{
		notempty->Acquire();
		while (count == 0)
			cond->Wait(notempty);
		notempty->Release();
		*(out_buf++) = buffer[read_pos];
		read_pos = (read_pos + 1) % buffer_size;
		notfull->Acquire();
		--count;
		cond->Signal(notfull);
		notfull->Release();
	}
}

void BoundedBuffer::Write(void *data, int size)
{
	char *in_buf = (char *) data;
	while(size--)
	{
		notfull->Acquire();
		while (count >= buffer_size)
			cond->Wait(notfull);
		notfull->Release();
		buffer[write_pos] = *(in_buf++);
		write_pos = (write_pos + 1) % buffer_size;
		notempty->Acquire();
		++count;
		cond->Signal(notempty);
		notempty->Release();
	}
}
