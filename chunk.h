#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
	OP_CONSTANT,
	OP_RETURN,
} opCode;

typedef struct {
	int count;
	int capacity;
	uint8_t *code;
	int *lines;
	valueArray constants;
} chunk;

void initChunk(chunk *chunk);
void freeChunk(chunk *chunk);
void writeChunk(chunk *chunk, uint8_t byte, int line);
int addConstant(chunk *chunk, value value);

#endif
