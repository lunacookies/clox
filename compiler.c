#include <stdio.h>

#include "compiler.h"
#include "scanner.h"

void
Compile(const char* Source)
{
	InitializeScanner(Source);
	u16 Line = -1;
	for (;;)
	{
		token Token = ScanToken();
		if (Token.Line != Line)
		{
			printf("%4d ", Token.Line);
			Line = Token.Line;
		}
		else
		{
			printf("   | ");
		}
		printf("%2d '%.*s'\n", Token.Type, Token.Length, Token.Start);

		if (Token.Type == TOKEN_EOF)
			break;
	}
}
