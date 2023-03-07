#include "matrix.h"
#include "macros.h"

CONSTRUCT_STRUCT(matrix);

matrix* init_matrix(int row, int column)
{
	int size = row * column * VOID_PTR_SIZE;
	matrix* mat_ptr = create_matrix();
	if (mat_ptr == NULL) return NULL;
	void** temp = (void**)malloc(size);
	if (temp == NULL) return mat_ptr;
	mat_ptr->data = temp;
	mat_ptr->row = row;
	mat_ptr->column = column;
	return mat_ptr;
}

void matrix_set_data(matrix* mat_ptr, int row, int column, void* value)
{
	if (mat_ptr == NULL) return;
	if (row < 0 || row >= mat_ptr->row) return;
	if (column < 0 || column >= mat_ptr->column) return;

	int index = row * mat_ptr->column + column;
	mat_ptr->data[index] = value;
}

void* matrix_get_data(matrix* mat_ptr, int row, int column)
{
	if (mat_ptr == NULL) return NULL;
	if (row < 0 || row >= mat_ptr->row) return NULL;
	if (column < 0 || column >= mat_ptr->column) return NULL;

	int index = row * mat_ptr->column + column;
	return mat_ptr->data[index];
}

void matrix_clear(matrix* mat_ptr)
{
	if (mat_ptr == NULL) return;
	if (mat_ptr->data == NULL) return;

	int size = mat_ptr->row * mat_ptr->column * VOID_PTR_SIZE;
	memset(mat_ptr->data, 0, size);
}

void free_matrix(matrix* mat_ptr)
{
	if (mat_ptr == NULL) return;
	if (mat_ptr->data != NULL)
	{
		free(mat_ptr->data);

		mat_ptr->row = 0;
		mat_ptr->column = 0;
		mat_ptr->data = NULL;
	}
	destroy_matrix(mat_ptr);
	mat_ptr = NULL;
}