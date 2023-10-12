#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

vm Vm;

void initVm(void) {
}

void freeVm(void) {
}

static interpretResult run(void) {
#define readByte() (*Vm.ip++)
#define readConstant() (Vm.chunk->constants.values[readByte()])

	for (;;) {
#ifdef DebugTraceExecution
		disassembleInstruction(
		        Vm.chunk, cast(int)(Vm.ip - Vm.chunk->code));
#endif

		uint8_t instruction;
		switch (instruction = readByte()) {
		case OP_CONSTANT: {
			value constant = readConstant();
			printValue(constant);
			printf("\n");
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
