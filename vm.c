#include <stdio.h>

#include "compiler.h"
#include "debug.h"
#include "vm.h"

vm Vm;

static void
ResetStack(void)
{
	Vm.StackTop = Vm.Stack;
}

void
InitializeVm(void)
{
	ResetStack();
}

void
FreeVm(void)
{
}

void
Push(value Value)
{
	*Vm.StackTop = Value;
	Vm.StackTop++;
}

value
Pop(void)
{
	Vm.StackTop--;
	return *Vm.StackTop;
}

static interpret_result
Run(void)
{
#define READ_BYTE() (*Vm.Ip++)
#define READ_CONSTANT() (Vm.Chunk->Constants.Values[READ_BYTE()])
#define BINARY_OP(Op)                                                          \
	do                                                                     \
	{                                                                      \
		value B = Pop();                                               \
		value A = Pop();                                               \
		Push(A Op B);                                                  \
	} while (false)

	for (;;)
	{
#ifdef DEBUG_TRACE_EXECUTION
		printf("          ");
		for (value* Slot = Vm.Stack; Slot < Vm.StackTop; Slot++)
		{
			printf("[ ");
			PrintValue(*Slot);
			printf(" ]");
		}
		printf("\n");
		DisassembleInstruction(Vm.Chunk, Vm.Ip - Vm.Chunk->Code);
#endif

		u8 Instruction;
		switch (Instruction = READ_BYTE())
		{
		case OP_CONSTANT:
		{
			value Constant = READ_CONSTANT();
			Push(Constant);
			break;
		}

		case OP_ADD:
			BINARY_OP(+);
			break;
		case OP_SUBTRACT:
			BINARY_OP(-);
			break;
		case OP_MULTIPLY:
			BINARY_OP(*);
			break;
		case OP_DIVIDE:
			BINARY_OP(/);
			break;

		case OP_NEGATE:
			Push(-Pop());
			break;

		case OP_RETURN:
			PrintValue(Pop());
			printf("\n");
			return INTERPRET_OK;
		}
	}

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

interpret_result
Interpret(const char* Source)
{
	chunk Chunk;
	InitializeChunk(&Chunk);

	if (!Compile(Source, &Chunk))
	{
		FreeChunk(&Chunk);
		return INTERPRET_COMPILE_ERROR;
	}

	Vm.Chunk = &Chunk;
	Vm.Ip = Vm.Chunk->Code;

	interpret_result Result = Run();

	FreeChunk(&Chunk);
	return Result;
}
