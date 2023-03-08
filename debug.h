#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"
#include "common.h"

void DisassembleChunk(chunk* Chunk, const char* Name);
usize DisassembleInstruction(chunk* Chunk, usize Offset);

#endif
