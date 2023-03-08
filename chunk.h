#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum
{
	OP_CONSTANT,
	OP_RETURN,
} op_code;

typedef struct
{
	usize Count;
	usize Capacity;
	u8* Code;
	value_array Constants;
} chunk;

void InitializeChunk(chunk* Chunk);
void FreeChunk(chunk* Chunk);
void WriteChunk(chunk* Chunk, u8 Byte);
usize AddConstant(chunk* Chunk, value Value);

#endif
