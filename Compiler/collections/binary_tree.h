#pragma once

#include "data/macros.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct binary_tree_node
{
	void* data;
	struct binary_tree_node* parent;
	struct binary_tree_node* left;
	struct binary_tree_node* right;
}binary_tree_node;

// 二叉树 只包含两个子节点，据分左右
typedef struct binary_tree
{
	binary_tree_node* root;
	// 比较运算 -1右节点，1左节点，0相等
	cmp_collection_data* compare;
	// 移除
	del_collection_data* del;
}binary_tree;

binary_tree* init_binary_tree();
binary_tree* init_binary_tree_with_func(cmp_collection_data* compare, del_collection_data* del);
bool binary_tree_contains_data(binary_tree* tree_ptr, void* data);
void* binary_tree_find_data(binary_tree* tree_ptr, void* data);
void binary_tree_add_data(binary_tree* tree_ptr, void* data);
void binary_tree_update_data(binary_tree* tree_ptr, void* data);
void binary_tree_remove_data(binary_tree* tree_ptr, void* data);
void binary_tree_clear(binary_tree* tree_ptr);
void free_binary_tree(binary_tree* tree_ptr);

void binary_tree_node_foreach_LDR(binary_tree_node* node, foreach_collection_node* func, void* c);
void binary_tree_node_foreach_DLR(binary_tree_node* node, foreach_collection_node* func, void* c);
void binary_tree_node_foreach_LRD(binary_tree_node* node, foreach_collection_node* func, void* c);

void binary_tree_node_foreach_data_LDR(binary_tree_node* node, foreach_collection_data *func, void* c);
void binary_tree_node_foreach_data_DLR(binary_tree_node* node, foreach_collection_data *func, void* c);
void binary_tree_node_foreach_data_LRD(binary_tree_node* node, foreach_collection_data *func, void* c);

void* binary_tree_node_find_data_DLR(binary_tree_node* node, find_collection_data* func, void* c);

#ifdef __cplusplus
}
#endif