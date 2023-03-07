#include "vector.h"
#include "macros.h"

CONSTRUCT_STRUCT(vector);

vector* init_vector()
{
	vector* vector_ptr = create_vector();
	if (vector_ptr == NULL) return NULL;
	vector_ptr->capacity = COLLECTION_CAPACITY;
	vector_ptr->data = (void**)malloc(VOID_PTR_SIZE * vector_ptr->capacity);
	return vector_ptr;
}

vector* init_vector_with_func(cmp_collection_data* compare, del_collection_data* del)
{
	vector* vector_ptr = init_vector();
	if (vector_ptr == NULL) return NULL;
	vector_ptr->compare = compare;
	vector_ptr->del = del;
	return vector_ptr;
}

void vector_resize(vector* vector_ptr, int capacity)
{
	if (vector_ptr == NULL || capacity <= 0) return;
	if (capacity <= vector_ptr->capacity) return;

	void** data = (void**)malloc(VOID_PTR_SIZE * capacity);
	if (data != NULL && vector_ptr->data != NULL)
	{
		memcpy(data, vector_ptr->data, VOID_PTR_SIZE * vector_ptr->capacity);
		free(vector_ptr->data);
	}

	vector_ptr->data = data;
	vector_ptr->capacity = capacity;
}

int vector_index_of(vector* vector_ptr, void* data)
{
	if (vector_ptr == NULL || data == NULL) return -1;
	if (vector_ptr->compare == NULL || vector_ptr->data == NULL) return -1;

	for (int i = 0; i < vector_ptr->size; i++)
	{
		void* cur_data = vector_ptr->data[i];
		int ret = vector_ptr->compare(cur_data, data);
		if (ret == 0) return i;
	}

	return -1;
}
void* vector_get_data(vector* vector_ptr, int index)
{
	if (vector_ptr == NULL || index < 0 || index >= vector_ptr->size) return NULL;
	if (vector_ptr->data == NULL) return NULL;

	return vector_ptr->data[index];
}

bool vector_contains_data(vector* vector_ptr, void* data)
{
	if (vector_ptr == NULL || data == NULL) return false;
	if (vector_ptr->compare == NULL || vector_ptr->data == NULL) return false;

	for (int i = 0; i < vector_ptr->size; i++)
	{
		void* cur_data = vector_ptr->data[i];
		int ret = vector_ptr->compare(cur_data, data);
		if (ret == 0) return true;
	}

	return false;
}
void vector_add_data(vector* vector_ptr, void* data)
{
	if (vector_ptr == NULL || data == NULL) return;

	if (vector_ptr->size + 1 > vector_ptr->capacity)
	{
		int capacity = 2 * vector_ptr->capacity;
		vector_resize(vector_ptr, capacity);
	}

	vector_ptr->data[vector_ptr->size] = data;
	vector_ptr->size += 1;

}
void vector_remove_data(vector* vector_ptr, void* data)
{
	if (vector_ptr == NULL || data == NULL) return;
	if (vector_ptr->compare == NULL) return;

	int offset = -1;

	for (int i = 0; i < vector_ptr->size; i++)
	{
		void* cur_data = vector_ptr->data[i];
		int ret = vector_ptr->compare(cur_data, data);
		if (ret == 0)
		{
			offset = i;
			break;
		}
	}

	if (offset >= 0)
	{
		if (vector_ptr->del != NULL)
		{
			vector_ptr->del(vector_ptr->data[offset]);
		}
		vector_ptr->data[offset] = NULL;
		for (int i = offset; i < vector_ptr->size-1; i++)
		{
			vector_ptr->data[i] = vector_ptr->data[i + 1];
		}
		vector_ptr->size -= 1;
	}
}

void* vector_find_data(vector* vector_ptr, void* data)
{
	if (vector_ptr == NULL || data == NULL) return NULL;
	if (vector_ptr->size == 0) return NULL;
	if (vector_ptr->compare == NULL) return NULL;

	for (int i = 0; i < vector_ptr->size; i++)
	{
		int ret = vector_ptr->compare(vector_ptr->data[i], data);
		if (ret == 0) return vector_ptr->data[i];
	}

	return NULL;
}

void vector_foreach(vector* vector_ptr, foreach_collection_data *func, void* c)
{
	if (vector_ptr == NULL || func == NULL) return;

	for (int i = 0; i < vector_ptr->size; i++)
	{
		func(vector_ptr->data[i], c);
	}
}

void* vector_find_if(vector* vector_ptr, find_collection_data* func, void* c)
{
	if (vector_ptr == NULL || func == NULL) return NULL;

	for (int i = 0; i < vector_ptr->size; i++)
	{
		bool ret = func(vector_ptr->data[i], c);
		if (ret) return vector_ptr->data[i];
	}

	return NULL;
}

void vector_append_vector(vector* v1, vector* v2)
{
	if (v1 == NULL || v2 == NULL) return;
	for (int i = 0; i < v2->size; i++)
	{
		void* data = vector_get_data(v2, i);
		vector_add_data(v1, data);
	}
}

void* vector_get_front(vector* vector_ptr)
{
	if (vector_ptr == NULL) return NULL;
	if (vector_ptr->size == 0) return NULL;
	return vector_ptr->data[0];
}

void* vector_get_back(vector* vector_ptr)
{
	if (vector_ptr == NULL) return NULL;
	if (vector_ptr->size == 0) return NULL;
	return vector_ptr->data[vector_ptr->size - 1];
}

void vector_clear(vector* vector_ptr)
{
	if (vector_ptr == NULL) return;
	if (vector_ptr->capacity != 0)
	{
		for (int i = 0; i < vector_ptr->size; i++)
		{
			if (vector_ptr->del != NULL)
			{
				vector_ptr->del(vector_ptr->data[i]);
			}
		}

		free(vector_ptr->data);
	}
	vector_ptr->size = 0;
	vector_ptr->capacity = 0;
	vector_ptr->data = NULL;
}

void free_vector(vector* vector_ptr)
{
	if (vector_ptr == NULL) return;
	vector_clear(vector_ptr);
	destroy_vector(vector_ptr);
	vector_ptr = NULL;
}