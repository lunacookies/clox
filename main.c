#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int
main(int ArgumentCount, const char** Arguments)
{
	InitializeVm();

	chunk Chunk;
	InitializeChunk(&Chunk);

	u8 ConstantIndex = (u8)AddConstant(&Chunk, 1.2);
	WriteChunk(&Chunk, OP_CONSTANT, 123);
	WriteChunk(&Chunk, ConstantIndex, 123);

	ConstantIndex = (u8)AddConstant(&Chunk, 3.4);
	WriteChunk(&Chunk, OP_CONSTANT, 123);
	WriteChunk(&Chunk, ConstantIndex, 123);

	WriteChunk(&Chunk, OP_ADD, 123);

	ConstantIndex = (u8)AddConstant(&Chunk, 5.6);
	WriteChunk(&Chunk, OP_CONSTANT, 123);
	WriteChunk(&Chunk, ConstantIndex, 123);

	WriteChunk(&Chunk, OP_DIVIDE, 123);
	WriteChunk(&Chunk, OP_NEGATE, 123);

	WriteChunk(&Chunk, OP_RETURN, 123);

	DisassembleChunk(&Chunk, "test chunk");
	Interpret(&Chunk);
	FreeVm();
	FreeChunk(&Chunk);
	return 0;
}
