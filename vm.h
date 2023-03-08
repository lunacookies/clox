#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "common.h"

typedef struct
{
	chunk* Chunk;
	u8* Ip;
} vm;

typedef enum
{
	INTERPRET_OK,
	INTERPRET_COMPILE_ERROR,
	INTERPRET_RUNTIME_ERROR,
} interpret_result;

void InitializeVm(void);
void FreeVm(void);
interpret_result Interpret(chunk* Chunk);

#endif
