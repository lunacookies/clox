#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void
InitializeChunk(chunk* Chunk)
{
	Chunk->Count = 0;
	Chunk->Capacity = 0;
	Chunk->Code = NULL;
}

void
FreeChunk(chunk* Chunk)
{
	FREE_ARRAY(u8, Chunk->Code, Chunk->Capacity);
	InitializeChunk(Chunk);
}

void
WriteChunk(chunk* Chunk, u8 Byte)
{
	if (Chunk->Capacity < Chunk->Count + 1)
	{
		usize OldCapacity = Chunk->Capacity;
		Chunk->Capacity = GROW_CAPACITY(OldCapacity);
		Chunk->Code = GROW_ARRAY(
		        u8, Chunk->Code, OldCapacity, Chunk->Capacity);
	}

	Chunk->Code[Chunk->Count] = Byte;
	Chunk->Count++;
}