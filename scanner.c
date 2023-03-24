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

static bool
IsAtEnd(void)
{
	return *Scanner.Current == '\0';
}

static token
MakeToken(token_type Type)
{
	token Token;
	Token.Type = Type;
	Token.Start = Scanner.Start;
	Token.Length = (u16)(Scanner.Current - Scanner.Start);
	Token.Line = Scanner.Line;
	return Token;
}

static token
ErrorToken(const char* Message)
{
	token Token;
	Token.Type = TOKEN_ERROR;
	Token.Start = Message;
	Token.Length = (u16)strlen(Message);
	Token.Line = Scanner.Line;
	return Token;
}

token
ScanToken(void)
{
	Scanner.Start = Scanner.Current;

	if (IsAtEnd())
		return MakeToken(TOKEN_EOF);

	return ErrorToken("Unexpected character.");
}
