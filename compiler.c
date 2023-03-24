#include <stdio.h>

#include "compiler.h"
#include "scanner.h"

void
Compile(const char* Source)
{
	InitializeScanner(Source);
}
