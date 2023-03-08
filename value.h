#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef f64 value;

typedef struct
{
	usize Capacity;
	usize Count;
	value* Values;
} value_array;

void InitializeValueArray(value_array* Array);
void WriteValueArray(value_array* Array, value Value);
void FreeValueArray(value_array* Array);
void PrintValue(value Value);

#endif
