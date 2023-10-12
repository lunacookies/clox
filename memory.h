#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define growCapacity(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define freeArray(type, pointer, old_count) \
	reallocate(pointer, sizeof(type) * (old_count), 0)

#define growArray(type, pointer, old_count, new_count) \
	(type *)reallocate(pointer, sizeof(type) * (old_count), \
	        sizeof(type) * (new_count))

void *reallocate(void *pointer, size_t old_size, size_t new_size);

#endif
