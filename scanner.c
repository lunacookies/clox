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
IsDigit(char C)
{
	return C >= '0' && C <= '9';
}

static bool
IsAtEnd(void)
{
	return *Scanner.Current == '\0';
}

static char
Advance(void)
{
	Scanner.Current++;
	return Scanner.Current[-1];
}

static char
Peek(void)
{
	return *Scanner.Current;
}

static char
PeekNext(void)
{
	if (IsAtEnd())
		return '\0';
	return Scanner.Current[1];
}

static bool
Match(char Expected)
{
	if (IsAtEnd())
		return false;
	if (*Scanner.Current != Expected)
		return false;
	Scanner.Current++;
	return true;
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

static void
SkipWhitespace(void)
{
	for (;;)
	{
		char C = Peek();
		switch (C)
		{
		case ' ':
		case '\r':
		case '\t':
			Advance();
			break;
		case '\n':
			Scanner.Line++;
			Advance();
			break;
		case '/':
			if (PeekNext() == '/')
				// A comment goes until the end of the line.
				while (Peek() != '\n' && !IsAtEnd())
					Advance();
			else
				return;
			break;
		default:
			return;
		}
	}
}

static token
Number(void)
{
	while (IsDigit(Peek()))
		Advance();

	// Look for a fractional part.
	if (Peek() == '.' && IsDigit(PeekNext()))
	{
		// Consume the “.”.
		Advance();

		while (IsDigit(Peek()))
			Advance();
	}

	return MakeToken(TOKEN_NUMBER);
}

static token
String(void)
{
	while (Peek() != '"' && !IsAtEnd())
	{
		if (Peek() == '\n')
			Scanner.Line++;
		Advance();
	}

	if (IsAtEnd())
		return ErrorToken("Unterminated string.");

	// The closing quote.
	Advance();
	return MakeToken(TOKEN_STRING);
}

token
ScanToken(void)
{
	SkipWhitespace();
	Scanner.Start = Scanner.Current;

	if (IsAtEnd())
		return MakeToken(TOKEN_EOF);

	char C = Advance();
	if (IsDigit(C))
		return Number();

	switch (C)
	{
	case '(':
		return MakeToken(TOKEN_LEFT_PAREN);
	case ')':
		return MakeToken(TOKEN_RIGHT_PAREN);
	case '{':
		return MakeToken(TOKEN_LEFT_BRACE);
	case '}':
		return MakeToken(TOKEN_RIGHT_BRACE);
	case ';':
		return MakeToken(TOKEN_SEMICOLON);
	case ',':
		return MakeToken(TOKEN_COMMA);
	case '.':
		return MakeToken(TOKEN_DOT);
	case '-':
		return MakeToken(TOKEN_MINUS);
	case '+':
		return MakeToken(TOKEN_PLUS);
	case '/':
		return MakeToken(TOKEN_SLASH);
	case '*':
		return MakeToken(TOKEN_STAR);
	case '!':
		return MakeToken(Match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
	case '=':
		return MakeToken(Match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
	case '<':
		return MakeToken(Match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
	case '>':
		return MakeToken(
		        Match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
	case '"':
		return String();
	}

	return ErrorToken("Unexpected character.");
}
