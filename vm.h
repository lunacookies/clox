#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

typedef struct {
	chunk *chunk;
	uint8_t *ip;
} vm;

typedef enum {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
} interpretResult;

void initVm(void);
void freeVm(void);
interpretResult interpret(chunk *chunk);

#endif
