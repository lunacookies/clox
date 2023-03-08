#include "chunk.h"
#include "common.h"
#include "debug.h"

int
main(int ArgumentCount, const char** Arguments)
{
	chunk Chunk;
	InitializeChunk(&Chunk);

	u8 ConstantIndex = (u8)AddConstant(&Chunk, 1.2);
	WriteChunk(&Chunk, OP_CONSTANT, 123);
	WriteChunk(&Chunk, ConstantIndex, 123);

	WriteChunk(&Chunk, OP_RETURN, 123);

	DisassembleChunk(&Chunk, "test chunk");
	FreeChunk(&Chunk);
	return 0;
}
