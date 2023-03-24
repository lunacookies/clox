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

typedef enum
{
	PREC_NONE,
	PREC_ASSIGNMENT, // =
	PREC_OR, // or
	PREC_AND, // and
	PREC_EQUALITY, // == !=
	PREC_COMPARISON, // < > <= >=
	PREC_TERM, // + -
	PREC_FACTOR, // * /
	PREC_UNARY, // ! -
	PREC_CALL, // . ()
	PREC_PRIMARY
} precedence;

parser Parser;
chunk* CompilingChunk;

static chunk*
CurrentChunk(void)
{
	return CompilingChunk;
}

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

static void
EmitByte(u8 Byte)
{
	WriteChunk(CurrentChunk(), Byte, Parser.Previous.Line);
}

static void
EmitBytes(u8 Byte1, u8 Byte2)
{
	EmitByte(Byte1);
	EmitByte(Byte2);
}

static void
EmitReturn(void)
{
	EmitByte(OP_RETURN);
}

static u8
MakeConstant(value Value)
{
	usize Constant = AddConstant(CurrentChunk(), Value);
	if (Constant > UINT8_MAX)
	{
		Error("Too many constants in one chunk.");
		return 0;
	}

	return (u8)Constant;
}

static void
EmitConstant(value Value)
{
	EmitBytes(OP_CONSTANT, MakeConstant(Value));
}

static void
EndCompiler(void)
{
	EmitReturn();
}

static void
Grouping(void)
{
	Expression();
	Consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}

static void
Number(void)
{
	f64 Value = strtod(Parser.Previous.Start, NULL);
	EmitConstant(Value);
}

static void
Unary(void)
{
	token_type OperatorType = Parser.Previous.Type;

	// Compile the operand.
	ParsePrecedence(PREC_UNARY);

	// Emit the operator instruction.
	switch (OperatorType)
	{
	case TOKEN_MINUS:
		EmitByte(OP_NEGATE);
		break;
	default:
		return; // Unreachable.
	}
}

static void
ParsePrecedence(precedence Precedence)
{
}

static void
Expression(void)
{
	ParsePrecedence(PREC_ASSIGNMENT);
}

bool
Compile(const char* Source, chunk* Chunk)
{
	InitializeScanner(Source);
	CompilingChunk = Chunk;

	Parser.HadError = false;
	Parser.PanicMode = false;

	Advance();
	Expression();
	Consume(TOKEN_EOF, "Expect end of expression.");
	EndCompiler();
	return !Parser.HadError;
}
