#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double value;

typedef struct {
	int capacity;
	int count;
	value *values;
} valueArray;

void initValueArray(valueArray *array);
void writeValueArray(valueArray *array, value v);
void freeValueArray(valueArray *array);
void printValue(value value);

#endif
