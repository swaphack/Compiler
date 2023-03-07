#pragma once


#include "data/macros.h"
#include <stdint.h>
#include "binary_tree.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct set;

typedef struct set_value
{
	void* key;

	struct set* set;
}set_value;


typedef struct set
{
	binary_tree* tree;
	// ±»Ωœ‘ÀÀ„
	cmp_collection_data* compare;
	// “∆≥˝
	del_collection_data* del;
}set;


set* init_set();
set* init_set_with_func(cmp_collection_data* compare, del_collection_data* del);
bool set_contains_data(set* set_ptr, void* key);
void set_insert_data(set* set_ptr, void* key);
void set_remove_data(set* set_ptr, void* key);
void set_foreach(set* set_ptr, foreach_collection_data* func, void* c);
void* set_find_if(set* set_ptr, find_collection_data* func, void* c);
void set_clear(set* set_ptr);
void free_set(set* set_ptr);

#ifdef __cplusplus
}
#endif