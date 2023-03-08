#include <stdio.h>

#include "debug.h"
#include "value.h"

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
ConstantInstruction(const char* Name, chunk* Chunk, usize Offset)
{
	u8 ConstantIndex = Chunk->Code[Offset + 1];
	printf("%-16s %4d '", Name, ConstantIndex);
	PrintValue(Chunk->Constants.Values[ConstantIndex]);
	printf("'\n");
	return Offset + 2;
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
	case OP_CONSTANT:
		return ConstantInstruction("OP_CONSTANT", Chunk, Offset);
	case OP_RETURN:
		return SimpleInstruction("OP_RETURN", Offset);
	default:
		printf("Unknown opcode %d\n", Instruction);
		return Offset + 1;
	}
}
