#include "map.h"

CONSTRUCT_STRUCT(map);
CONSTRUCT_STRUCT(map_value);


int compare_map_node(void* a, void* b)
{
	map_value* aa = (map_value*)a;
	map_value* bb = (map_value*)b;
	if (aa->map != NULL && aa->map->compare != NULL)
	{
		return aa->map->compare(aa->key, bb->key);
	}
	return 0;
}

void del_map_node(void* a)
{
	if (a == NULL) return;
	map_value* aa = (map_value*)a;
	if (aa->map != NULL && aa->map->del != NULL)
	{
		aa->map->del(aa->key, aa->value);
	}
	free_map_value(aa);
}

map_value* init_map_value(void* key, void* data)
{
	map_value* value = create_map_value();
	value->key = key;
	value->value = data;
	return value;
}
void free_map_value(map_value* value)
{
	if (value == NULL) return;
	destroy_map_value(value);
}

map* init_map()
{
	map* map_ptr = create_map();
	if (map_ptr == NULL) return NULL;
	map_ptr->tree = init_binary_tree();
	if (map_ptr->tree != NULL)
	{
		map_ptr->tree->compare = compare_map_node;
		map_ptr->tree->del = del_map_node;
	}	
	return map_ptr;
}

map* init_map_with_func(cmp_collection_data* compare, del_map_data* del)
{
	map* map_ptr = init_map();
	if (map_ptr == NULL) return NULL;
	map_ptr->compare = compare;
	map_ptr->del = del;
	return map_ptr;
}


bool map_contains_key(map* map_ptr, void* key)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return false;

	map_value value;
	value.key = key;

	return binary_tree_contains_data(map_ptr->tree, &value);
}

void* map_get_value(map* map_ptr, void* key)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return false;

	map_value value;
	value.key = key;

	void* data = binary_tree_find_data(map_ptr->tree, &value);
	if (data == NULL) return NULL;
	return ((map_value*)data)->value;
}

void map_add_data(map* map_ptr, void* key, void* data)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return;

	map_value* value = init_map_value(key, data);
	value->map = map_ptr;
	binary_tree_update_data(map_ptr->tree, value);
}
void map_remove_data(map* map_ptr, void* key)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return;

	map_value value;
	value.key = key;

	binary_tree_remove_data(map_ptr->tree, &value);
}

void map_foreach(map* map_ptr, foreach_collection_data* func, void* c)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return;
	if (func == NULL) return;

	binary_tree_node_foreach_data_DLR(map_ptr->tree->root, func, c);
}

typedef struct map_foreach_data
{
	foreach_collection_data* func;
	void* c;
}map_foreach_data;

void foreach_map_key(void* a, void* b)
{
	map_value* value = (map_value*)a;
	map_foreach_data* bb = (map_foreach_data*)b;
	bb->func(value->key, bb->c);
}

void foreach_map_value(void* a, void* b)
{
	map_value* value = (map_value*)a;
	map_foreach_data* bb = (map_foreach_data*)b;
	bb->func(value->value, bb->c);
}

void map_foreach_key(map* map_ptr, foreach_collection_data* func, void* c)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return;
	if (func == NULL) return;

	map_foreach_data data;
	data.c = c;
	data.func = func;

	binary_tree_node_foreach_data_DLR(map_ptr->tree->root, foreach_map_key, &data);
}

void map_foreach_value(map* map_ptr, foreach_collection_data* func, void* c)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return;
	if (func == NULL) return;

	map_foreach_data data;
	data.c = c;
	data.func = func;

	binary_tree_node_foreach_data_DLR(map_ptr->tree->root, foreach_map_value, &data);
}

map_value* map_find_if(map* map_ptr, find_collection_data* func, void* c)
{
	if (map_ptr == NULL || map_ptr->tree == NULL) return NULL;
	if (func == NULL || c == NULL) return NULL;

	void* d = binary_tree_node_find_data_DLR(map_ptr->tree->root, func, c);

	return (map_value*)d;
}

void map_clear(map* map_ptr)
{
	if (map_ptr == NULL) return;

	binary_tree_clear(map_ptr->tree);
}

void free_map(map* map_ptr)
{
	if (map_ptr == NULL) return;
	if (map_ptr->tree != NULL)
	{
		free_binary_tree(map_ptr->tree);
		map_ptr->tree = NULL;
	}	
	destroy_map(map_ptr);
	map_ptr = NULL;
}


