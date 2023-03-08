#include "chunk.h"
#include "common.h"
#include "debug.h"

int
main(int ArgumentCount, const char** Arguments)
{
	chunk Chunk;
	InitializeChunk(&Chunk);
	WriteChunk(&Chunk, OP_RETURN);

	DisassembleChunk(&Chunk, "test chunk");
	FreeChunk(&Chunk);
	return 0;
}
