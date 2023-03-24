#include <stdio.h>
#include <string.h>

#include "scanner.h"

typedef struct
{
	const char* Start;
	const char* Current;
	u16 Line;
} scanner;

scanner Scanner;

void
InitializeScanner(const char* Source)
{
	Scanner.Start = Source;
	Scanner.Current = Source;
	Scanner.Line = 1;
}
