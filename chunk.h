#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum {
	OP_RETURN,
} opCode;

typedef struct {
	int count;
	int capacity;
	uint8_t *code;
} chunk;

void initChunk(chunk *chunk);
void freeChunk(chunk *chunk);
void writeChunk(chunk *chunk, uint8_t byte);

#endif
