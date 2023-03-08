#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum
{
	OP_RETURN,
} op_code;

typedef struct
{
	usize Count;
	usize Capacity;
	u8* Code;
} chunk;

void InitializeChunk(chunk* Chunk);
void FreeChunk(chunk* Chunk);
void WriteChunk(chunk* Chunk, u8 Byte);

#endif
