#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

vm Vm;

static void resetStack(void) {
	Vm.stack_top = Vm.stack;
}

void initVm(void) {
	resetStack();
}

void freeVm(void) {
}

void push(value value) {
	*Vm.stack_top = value;
	Vm.stack_top++;
}

value pop(void) {
	Vm.stack_top--;
	return *Vm.stack_top;
}

static interpretResult run(void) {
#define readByte() (*Vm.ip++)
#define readConstant() (Vm.chunk->constants.values[readByte()])

	for (;;) {
#ifdef DebugTraceExecution
		printf("          ");
		for (value *slot = Vm.stack; slot < Vm.stack_top; slot++) {
			printf("[ ");
			printValue(*slot);
			printf(" ]");
		}
		printf("\n");
		disassembleInstruction(
		        Vm.chunk, cast(int)(Vm.ip - Vm.chunk->code));
#endif

		uint8_t instruction;
		switch (instruction = readByte()) {
		case OP_CONSTANT: {
			value constant = readConstant();
			push(constant);
			break;
		}

		case OP_RETURN: {
			return INTERPRET_OK;
		}
		}
	}

#undef readByte
#undef readConstant
}

interpretResult interpret(chunk *chunk) {
	Vm.chunk = chunk;
	Vm.ip = Vm.chunk->code;
	return run();
}
