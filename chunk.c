#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(chunk *chunk) {
	chunk->count = 0;
	chunk->capacity = 0;
	chunk->code = NULL;
	chunk->lines = NULL;
	initValueArray(&chunk->constants);
}

void freeChunk(chunk *chunk) {
	freeArray(uint8_t, chunk->code, cast(size_t) chunk->capacity);
	freeArray(int, chunk->lines, cast(size_t) chunk->capacity);
	freeValueArray(&chunk->constants);
	initChunk(chunk);
}

void writeChunk(chunk *chunk, uint8_t byte, int line) {
	if (chunk->capacity < chunk->count + 1) {
		int old_capacity = chunk->capacity;
		chunk->capacity = growCapacity(old_capacity);
		chunk->code = growArray(uint8_t, chunk->code,
		        cast(size_t) old_capacity,
		        cast(size_t) chunk->capacity);
		chunk->lines =
		        growArray(int, chunk->lines, cast(size_t) old_capacity,
		                cast(size_t) chunk->capacity);
	}

	chunk->code[chunk->count] = byte;
	chunk->lines[chunk->count] = line;
	chunk->count++;
}

int addConstant(chunk *chunk, value value) {
	writeValueArray(&chunk->constants, value);
	return chunk->constants.count - 1;
}
