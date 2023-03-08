#include <stdio.h>

#include "debug.h"

void
DisassembleChunk(chunk* Chunk, const char* Name)
{
	printf("== %s ==\n", Name);

	for (usize Offset = 0; Offset < Chunk->Count;)
	{
		Offset = DisassembleInstruction(Chunk, Offset);
	}
}

static usize
SimpleInstruction(const char* Name, usize Offset)
{
	printf("%s\n", Name);
	return Offset + 1;
}

usize
DisassembleInstruction(chunk* Chunk, usize Offset)
{
	printf("%04zu ", Offset);

	u8 Instruction = Chunk->Code[Offset];
	switch (Instruction)
	{
	case OP_RETURN:
		return SimpleInstruction("OP_RETURN", Offset);
	default:
		printf("Unknown opcode %d\n", Instruction);
		return Offset + 1;
	}
}
