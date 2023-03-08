#include <stdio.h>

#include "debug.h"
#include "vm.h"

vm Vm;

void
InitializeVm(void)
{
}

void
FreeVm(void)
{
}

static interpret_result
Run(void)
{
#define READ_BYTE() (*Vm.Ip++)
#define READ_CONSTANT() (Vm.Chunk->Constants.Values[READ_BYTE()])

	for (;;)
	{
#ifdef DEBUG_TRACE_EXECUTION
		DisassembleInstruction(Vm.Chunk, Vm.Ip - Vm.Chunk->Code);
#endif

		u8 Instruction;
		switch (Instruction = READ_BYTE())
		{
		case OP_CONSTANT:
		{
			value Constant = READ_CONSTANT();
			PrintValue(Constant);
			printf("\n");
			break;
		}
		case OP_RETURN:
			return INTERPRET_OK;
		}
	}

#undef READ_BYTE
#undef READ_CONSTANT
}

interpret_result
Interpret(chunk* Chunk)
{
	Vm.Chunk = Chunk;
	Vm.Ip = Vm.Chunk->Code;
	return Run();
}
