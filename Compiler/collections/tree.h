#pragma once

#include "macros.h"
#include "vector.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct tree_node
{
	// 数据
	void* data;
	// 父节点
	struct tree_node* parent;
	// 子节点 {tree_node*}
	vector* children;
	// 树
	struct tree* tree;
}tree_node;

// 树节点 根据包含范围判定界限，
typedef struct tree
{
	tree_node* root;
	// 比较运算 >=0包含，0相等, -1不包含
	cmp_collection_data* compare;
	// 移除
	del_collection_data* del;
}tree;

tree_node* init_tree_node(void* data, tree* tree);
void free_tree_node(tree_node* tn_ptr);
tree_node* tree_node_find_child(tree_node* tn_ptr, void* data);
tree_node* tree_node_get_child(tree_node* tn_ptr, int index);
void tree_node_add_child(tree_node* tn_ptr, tree_node* child);
void tree_node_remove_child_and_cleanup(tree_node* tn_ptr, tree_node* child, bool bcleanup);
void tree_node_remove_child(tree_node* tn_ptr, tree_node* child);
void tree_node_remove_all_children(tree_node* tn_ptr);
// 从根节点开始的层数
int tree_node_get_distance_from_root(tree_node* tn_ptr);
// 同辈位置
int tree_node_get_index_from_peer(tree_node* tn_ptr);

tree* init_tree();
tree* init_tree_with_func(cmp_collection_data* compare, del_collection_data* del);
bool tree_contains_data(tree* tree_ptr, void* data);
void* tree_find_data(tree* tree_ptr, void* data);
void tree_add_data(tree* tree_ptr, void* data);
void tree_remove_data(tree* tree_ptr, void* data);

void tree_add_node(tree* tree_ptr, tree_node* node_ptr);
void tree_remove_node(tree* tree_ptr, tree_node* node_ptr);

void tree_node_foreach(tree_node* node, foreach_collection_node* func, void* c);
void tree_node_foreach_data(tree_node* node, foreach_collection_data* func, void* c);
void* tree_node_find_data(tree_node* node, find_collection_data* func, void* c);

void tree_clear(tree* tree_ptr);
void free_tree(tree* tree_ptr);

int compare_tree_node(void* a, void* b);
void del_tree_node(void* a);

#ifdef __cplusplus
}
#endif