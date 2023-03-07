#include "set.h"

CONSTRUCT_STRUCT(set);
CONSTRUCT_STRUCT(set_value);

int compare_set_node(void* a, void* b)
{
	set_value* aa = (set_value*)a;
	set_value* bb = (set_value*)b;
	if (aa->set != NULL && aa->set->compare != NULL)
	{
		return aa->set->compare(aa->key, bb->key);
	}
	return 0;
}

void del_set_node(void* a)
{
	if (a == NULL) return;
	set_value* aa = (set_value*)a;
	if (aa->set != NULL && aa->set->del != NULL)
	{
		aa->set->del(aa->key);
	}
	destroy_set_value(aa);
}

set* init_set()
{
	set* set_ptr = create_set();
	if (set_ptr == NULL) return NULL;
	set_ptr->tree = init_binary_tree();
	if (set_ptr->tree != NULL)
	{
		set_ptr->tree->compare = compare_set_node;
		set_ptr->tree->del = del_set_node;
	}
	
	return set_ptr;
}

set* init_set_with_func(cmp_collection_data* compare, del_collection_data* del)
{
	set* set_ptr = init_set();
	if (set_ptr == NULL) return NULL;

	set_ptr->compare = compare;
	set_ptr->del = del;
	return set_ptr;
}

bool set_contains_data(set* set_ptr, void* key)
{
	if (set_ptr == NULL || set_ptr->tree == NULL) return false;

	set_value value;
	value.key = key;
	return binary_tree_contains_data(set_ptr->tree, &value);
}

void set_insert_data(set* set_ptr, void* key)
{
	if (set_ptr == NULL || set_ptr->tree == NULL) return;

	set_value* value = create_set_value();
	value->key = key;
	value->set = set_ptr;
	binary_tree_add_data(set_ptr->tree, value);
}

void set_remove_data(set* set_ptr, void* key)
{
	if (set_ptr == NULL || set_ptr->tree == NULL) return;

	set_value value;
	value.key = key;

	binary_tree_remove_data(set_ptr->tree, &value);
}

void set_foreach(set* set_ptr, foreach_collection_data *func, void* c)
{
	if (set_ptr == NULL || set_ptr->tree == NULL) return;
	if (func == NULL) return;

	binary_tree_node_foreach_DLR(set_ptr->tree->root, func, c);
}

void* set_find_if(set* set_ptr, find_collection_data* func, void* c)
{
	if (set_ptr == NULL || set_ptr->tree == NULL) return NULL;
	if (func == NULL) return NULL;

	void* data = binary_tree_node_find_data_DLR(set_ptr->tree->root, func, c);
	if (data == NULL) return NULL;
	return ((set_value*)data)->key;
}

void set_clear(set* set_ptr)
{
	if (set_ptr == NULL) return;

	binary_tree_clear(set_ptr->tree);
}

void free_set(set* set_ptr)
{
	if (set_ptr == NULL) return;

	free_binary_tree(set_ptr->tree);
	free(set_ptr);
	set_ptr = NULL;
}