#include <stdio.h>
#include <stdlib.h>

#include "compiler.h"
#include "scanner.h"

typedef struct
{
	token Current;
	token Previous;
	bool HadError;
	bool PanicMode;
} parser;

parser Parser;

static void
ErrorAt(token* Token, const char* Message)
{
	if (Parser.PanicMode)
		return;
	Parser.PanicMode = true;
	fprintf(stderr, "[line %d], Error", Token->Line);

	if (Token->Type == TOKEN_EOF)
	{
		fprintf(stderr, " at end");
	}
	else if (Token->Type == TOKEN_ERROR)
	{
		// Nothing.
	}
	else
	{
		fprintf(stderr, " at '%.*s'", Token->Length, Token->Start);
	}

	fprintf(stderr, ": %s\n", Message);
	Parser.HadError = true;
}

static void
Error(const char* Message)
{
	ErrorAt(&Parser.Previous, Message);
}

static void
ErrorAtCurrent(const char* Message)
{
	ErrorAt(&Parser.Current, Message);
}

static void
Advance(void)
{
	Parser.Previous = Parser.Current;

	for (;;)
	{
		Parser.Current = ScanToken();
		if (Parser.Current.Type != TOKEN_ERROR)
			break;

		ErrorAtCurrent(Parser.Current.Start);
	}
}

static void
Consume(token_type Type, const char* Message)
{
	if (Parser.Current.Type == Type)
	{
		Advance();
		return;
	}

	ErrorAtCurrent(Message);
}

bool
Compile(const char* Source, chunk* Chunk)
{
	InitializeScanner(Source);

	Parser.HadError = false;
	Parser.PanicMode = false;

	Advance();
	Expression();
	Consume(TOKEN_EOF, "Expect end of expression.");
	return !Parser.HadError;
}
