#include "list.h"

CONSTRUCT_STRUCT(list);
CONSTRUCT_STRUCT(list_node);

REMOVE_NODE_DATA(list, list_node);

list* init_list()
{
	list* list_ptr = create_list();
	return list_ptr;
}

list* init_list_with_func(cmp_collection_data* compare, del_collection_data* del)
{
	list* list_ptr = create_list();
	if (list_ptr == NULL) return NULL;
	list_ptr->compare = compare;
	list_ptr->del = del;
	return list_ptr;
}

bool list_contains_data(list* list_ptr, void* data)
{
	if (list_ptr == NULL || data == NULL) return false;

	if (list_ptr->compare == NULL) return false;

	list_node* node = list_ptr->root;
	while (node != NULL)
	{
		int ret = list_ptr->compare(node->data, data);
		if (ret == 0) return true;
		
		node = node->next;
	}
	return false;
}

void* list_find_data(list* list_ptr, void* data)
{
	if (list_ptr == NULL || data == NULL) return NULL;

	if (list_ptr->compare == NULL) return NULL;

	list_node* node = list_ptr->root;
	while (node != NULL)
	{
		int ret = list_ptr->compare(node->data, data);
		if (ret == 0) return node->data;

		node = node->next;
	}
	return NULL;
}

void list_foreach(list* list_ptr, foreach_collection_data* func, void* c)
{
	if (list_ptr == NULL || func == NULL) return;
	list_node* node = list_ptr->root;
	while (node != NULL)
	{
		func(node->data, c);
		node = node->next;
	}
}

void* list_find_if(list* list_ptr, find_collection_data* func, void* c)
{
	if (list_ptr == NULL || func == NULL) return false;
	list_node* node = list_ptr->root;
	while (node != NULL)
	{
		bool ret = func(node->data, c);
		if (ret) return node->data;
		node = node->next;
	}
	return NULL;
}

void list_append_data(list* list_ptr, void* data)
{
	if (list_ptr == NULL || data == NULL) return;

	list_node* last_node = create_list_node();
	if (last_node == NULL) return;
	last_node->data = data;

	list_node* node = list_ptr->root;
	if (node == NULL)
	{
		list_ptr->root = last_node;
	}
	else
	{
		while (node != NULL)
		{
			if (node->next == NULL)
			{
				break;
			}
			node = node->next;
		}
		if (node == NULL) return;
		node->next = last_node;
	}	
}

void list_remove_data(list* list_ptr, void* data)
{
	if (list_ptr == NULL || data == NULL) return;
	list_node* node = list_ptr->root;
	list_node* pre_node = NULL;
	while (node != NULL)
	{
		int ret = list_ptr->compare(node->data, data);
		if (ret == 0) break;
		pre_node = node;
		node = node->next;
	}

	if (node == NULL) return;
	struct list_node* cur_node = node;
	if (pre_node == NULL)
	{// Ê×½Úµã
		list_ptr->root = node->next;
	}
	else
	{
		pre_node->next = node->next;
	}
	remove_list_node_data(list_ptr, cur_node);
	destroy_list_node(cur_node);
}

void list_clear(list* list_ptr)
{
	if (list_ptr == NULL) return;

	list_node* node = list_ptr->root;
	while (node != NULL)
	{
		struct list_node* next = node->next;
		remove_list_node_data(list_ptr, node);
		destroy_list_node(node);
		node = next;
	}
	list_ptr->root = NULL;
}

int list_get_size(list* list_ptr)
{
	if (list_ptr == NULL) return 0;

	int count = 0;
	list_node* node = list_ptr->root;
	while (node != NULL)
	{
		count++;
		node = node->next;
	}
	return count;
}


void free_list(list* list_ptr)
{
	if (list_ptr == NULL) return;

	list_clear(list_ptr);
	destroy_list(list_ptr);
}
