#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define StackMax 256

typedef struct {
	chunk *chunk;
	uint8_t *ip;
	value stack[StackMax];
	value *stack_top;
} vm;

typedef enum {
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
} interpretResult;

void initVm(void);
void freeVm(void);
interpretResult interpret(chunk *chunk);
void push(value value);
value pop(void);

#endif
