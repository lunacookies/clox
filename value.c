#include <stdio.h>

#include "memory.h"
#include "value.h"

void
InitializeValueArray(value_array* Array)
{
	Array->Values = NULL;
	Array->Capacity = 0;
	Array->Count = 0;
}

void
WriteValueArray(value_array* Array, value Value)
{
	if (Array->Capacity < Array->Count + 1)
	{
		usize OldCapacity = Array->Capacity;
		Array->Capacity = GROW_CAPACITY(OldCapacity);
		Array->Values = GROW_ARRAY(
		        value, Array->Values, OldCapacity, Array->Capacity);
	}

	Array->Values[Array->Count] = Value;
	Array->Count++;
}

void
FreeValueArray(value_array* Array)
{
	FREE_ARRAY(value, Array->Values, Array->Capacity);
	InitializeValueArray(Array);
}

void
PrintValue(value Value)
{
	printf("%g", Value);
}
