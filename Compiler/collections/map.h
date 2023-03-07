#pragma once

#include "data/macros.h"
#include <stdint.h>
#include "binary_tree.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct map;

typedef struct map_value
{
	void* key;
	void* value;
	struct map* map;
}map_value;

typedef struct map
{
	binary_tree* tree;
	// ±»Ωœ‘ÀÀ„
	cmp_collection_data* compare;
	// “∆≥˝
	del_map_data* del;
}map;

map_value* init_map_value(void* key, void* data);
void free_map_value(map_value* value);

map* init_map();
map* init_map_with_func(cmp_collection_data* compare, del_map_data* del);
bool map_contains_key(map* map_ptr, void* key);
void* map_get_value(map* map_ptr, void* key);
void map_add_data(map* map_ptr, void* key, void* data);
void map_remove_data(map* map_ptr, void* key);
void map_foreach(map* map_ptr, foreach_collection_data* func, void* c);
void map_foreach_key(map* map_ptr, foreach_collection_data* func, void* c);
void map_foreach_value(map* map_ptr, foreach_collection_data* func, void* c);
map_value* map_find_if(map* map_ptr, find_collection_data* func, void* c);
void map_clear(map* map_ptr);
void free_map(map* map_ptr);

#ifdef __cplusplus
}
#endif