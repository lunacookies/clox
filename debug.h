#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(chunk *chunk, const char *name);
int disassembleInstruction(chunk *chunk, int offset);

#endif
