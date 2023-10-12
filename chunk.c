#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(chunk *chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
}

void freeChunk(chunk *chunk) {
	freeArray(uint8_t, chunk->code, cast(size_t) chunk->capacity);
	initChunk(chunk);
}

void writeChunk(chunk *chunk, uint8_t byte) {
	if (chunk->capacity < chunk->count + 1) {
		int old_capacity = chunk->capacity;
		chunk->capacity = growCapacity(old_capacity);
		chunk->code = growArray(uint8_t, chunk->code,
		        cast(size_t) old_capacity,
		        cast(size_t) chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	chunk->count++;
}
