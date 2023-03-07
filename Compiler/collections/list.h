#pragma once

#include "data/macros.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct list_node
{
	void* data;
	struct list_node* next;
}list_node;


// 链表
typedef struct list
{
	// 根节点
	list_node* root;
	// 比较运算
	cmp_collection_data *compare;
	// 移除
	del_collection_data* del;
}list;

list* init_list();
list* init_list_with_func(cmp_collection_data *compare, del_collection_data *del);
bool list_contains_data(list* list_ptr, void* data);
void* list_find_data(list* list_ptr, void* data);
void list_foreach(list* list_ptr, foreach_collection_data*func, void* c);
void* list_find_if(list* list_ptr, find_collection_data* func, void* c);

void list_append_data(list* list_ptr, void* data);
void list_remove_data(list* list_ptr, void* data);
void list_clear(list* list_ptr);
int list_get_size(list* list_ptr);

void free_list(list* list_ptr);

#ifdef __cplusplus
}
#endif