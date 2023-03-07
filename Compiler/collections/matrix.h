#pragma once

#include "data/macros.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct matrix
{
	void** data;
	int row;
	int column;
}matrix;

matrix* init_matrix(int row, int column);
void matrix_set_data(matrix* mat_ptr, int row, int column, void* value);
void* matrix_get_data(matrix* mat_ptr, int row, int column);
void matrix_clear(matrix* mat_ptr);
void free_matrix(matrix* mat_ptr);


#ifdef __cplusplus
}
#endif