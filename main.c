#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

static void
Repl(void)
{
	char Line[1024];
	for (;;)
	{
		printf("> ");

		if (!fgets(Line, sizeof(Line), stdin))
		{
			printf("\n");
			break;
		}

		Interpret(Line);
	}
}

static u8*
ReadFile(const char* Path)
{
	FILE* File = fopen(Path, "rb");
	if (File == NULL)
	{
		fprintf(stderr, "Could not open file “%s”.\n", Path);
		exit(74);
	}

	fseek(File, 0L, SEEK_END);
	usize FileSize = ftell(File);
	rewind(File);

	u8* Buffer = malloc(FileSize + 1);
	if (Buffer == NULL)
	{
		fprintf(stderr, "Not enough memory to read “%s”.\n", Path);
		exit(74);
	}

	usize BytesRead = fread(Buffer, 1, FileSize, File);
	if (BytesRead < FileSize)
	{
		fprintf(stderr, "Could not read file “%s”.\n", Path);
		exit(74);
	}

	Buffer[BytesRead] = '\0';

	fclose(File);
	return Buffer;
}

static void
RunFile(const char* Path)
{
	char* Source = (char*)ReadFile(Path);
	interpret_result Result = Interpret(Source);
	free(Source);

	if (Result == INTERPRET_COMPILE_ERROR)
		exit(65);
	if (Result == INTERPRET_RUNTIME_ERROR)
		exit(70);
}

int
main(int ArgumentCount, const char** Arguments)
{
	InitializeVm();

	if (ArgumentCount == 1)
		Repl();
	else if (ArgumentCount == 2)
		RunFile(Arguments[1]);
	else
	{
		fprintf(stderr, "Usage: clox [path]\n");
		exit(64);
	}

	FreeVm();
	return 0;
}
