#pragma once


#include "data/macros.h"
#include "macros.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct vector
{
	void** data;
	int size;
	int capacity;

	// 比较运算
	cmp_collection_data* compare;
	// 移除
	del_collection_data* del;
}vector;

vector* init_vector();
vector* init_vector_with_func(cmp_collection_data* compare, del_collection_data* del);
void vector_resize(vector* vector_ptr, int capacity);
int vector_index_of(vector* vector_ptr, void* data);
void* vector_get_data(vector* vector_ptr, int index);
bool vector_contains_data(vector* vector_ptr, void* data);
void vector_add_data(vector* vector_ptr, void* data);
void vector_remove_data(vector* vector_ptr, void* data);
void* vector_find_data(vector* vector_ptr, void* data);
void vector_foreach(vector* vector_ptr, foreach_collection_data* func, void* c);
void* vector_find_if(vector* vector_ptr, find_collection_data* func, void* c);
// v2 追加到v1后边
void vector_append_vector(vector* v1, vector* v2);
void* vector_get_front(vector* vector_ptr);
void* vector_get_back(vector* vector_ptr);

void vector_clear(vector* vector_ptr);
void free_vector(vector* vector_ptr);

#ifdef __cplusplus
}
#endif