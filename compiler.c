#include <stdio.h>

#include "compiler.h"
#include "scanner.h"

bool
Compile(const char* Source, chunk* Chunk)
{
	InitializeScanner(Source);
	Advance();
	Expression();
	Consume(TOKEN_EOF, "Expect end of expression.");
}
