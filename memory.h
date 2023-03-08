#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(Capacity) ((Capacity) < 8 ? 8 : (Capacity)*2)

#define GROW_ARRAY(Type, Pointer, OldCount, NewCount)                          \
	(Type*)Reallocate(                                                     \
	        Pointer, sizeof(Type) * (OldCount), sizeof(Type) * (NewCount))

#define FREE_ARRAY(Type, Pointer, OldCount)                                    \
	Reallocate(Pointer, sizeof(Type) * (OldCount), 0)

void* Reallocate(void* Pointer, usize OldSize, usize NewSize);

#endif
