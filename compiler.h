#ifndef clox_compiler_h
#define clox_compiler_h

#include "common.h"
#include "vm.h"

bool Compile(const char* Source, chunk* Chunk);

#endif
