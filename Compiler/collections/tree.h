#pragma once

#include "macros.h"
#include "vector.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef struct tree_node
{
	// ����
	void* data;
	// ���ڵ�
	struct tree_node* parent;
	// �ӽڵ� {tree_node*}
	vector* children;
	// ��
	struct tree* tree;
}tree_node;

// ���ڵ� ���ݰ�����Χ�ж����ޣ�
typedef struct tree
{
	tree_node* root;
	// �Ƚ����� >=0������0���, -1������
	cmp_collection_data* compare;
	// �Ƴ�
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
// �Ӹ��ڵ㿪ʼ�Ĳ���
int tree_node_get_distance_from_root(tree_node* tn_ptr);
// ͬ��λ��
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