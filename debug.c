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
	if (Offset > 0 && Chunk->Lines[Offset] == Chunk->Lines[Offset - 1])
		printf("   | ");
	else
		printf("%4d ", Chunk->Lines[Offset]);

	u8 Instruction = Chunk->Code[Offset];
	switch (Instruction)
	{
	case OP_CONSTANT:
		return ConstantInstruction("OP_CONSTANT", Chunk, Offset);
	case OP_ADD:
		return SimpleInstruction("OP_ADD", Offset);
	case OP_SUBTRACT:
		return SimpleInstruction("OP_SUBTRACT", Offset);
	case OP_MULTIPLY:
		return SimpleInstruction("OP_MULTIPLY", Offset);
	case OP_DIVIDE:
		return SimpleInstruction("OP_DIVIDE", Offset);
	case OP_NEGATE:
		return SimpleInstruction("OP_NEGATE", Offset);
	case OP_RETURN:
		return SimpleInstruction("OP_RETURN", Offset);
	default:
		printf("Unknown opcode %d\n", Instruction);
		return Offset + 1;
	}
}
