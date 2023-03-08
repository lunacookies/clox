#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum
{
	OP_CONSTANT,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_NEGATE,
	OP_RETURN,
} op_code;

typedef struct
{
	usize Count;
	usize Capacity;
	u8* Code;
	u16* Lines;
	value_array Constants;
} chunk;

void InitializeChunk(chunk* Chunk);
void FreeChunk(chunk* Chunk);
void WriteChunk(chunk* Chunk, u8 Byte, u16 Line);
usize AddConstant(chunk* Chunk, value Value);

#endif
