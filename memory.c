#include <stdlib.h>

#include "memory.h"

void*
Reallocate(void* Pointer, usize OldSize, usize NewSize)
{
	if (NewSize == 0)
	{
		free(Pointer);
		return NULL;
	}

	void* Result = realloc(Pointer, NewSize);
	if (Result == NULL)
		exit(1);
	return Result;
}
