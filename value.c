#include <stdio.h>

#include "memory.h"
#include "value.h"

void initValueArray(valueArray *array) {
	array->values = NULL;
	array->capacity = 0;
	array->count = 0;
}

void writeValueArray(valueArray *array, value v) {
	if (array->capacity < array->count + 1) {
		int old_capacity = array->capacity;
		array->capacity = growCapacity(old_capacity);
		array->values = growArray(value, array->values,
		        cast(size_t) old_capacity,
		        cast(size_t) array->capacity);
	}

	array->values[array->count] = v;
	array->count++;
}

void freeValueArray(valueArray *array) {
	freeArray(value, array->values, cast(size_t) array->capacity);
	initValueArray(array);
}

void printValue(value value) {
	printf("%g", value);
}
