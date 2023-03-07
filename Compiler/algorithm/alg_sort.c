#include "alg_sort.h"
#include "collections/vector.h"
#include "collections/tree.h"


void sort_vector(struct vector* vector_ptr, alg_compare_priority* func)
{
	if (vector_ptr == NULL || func == NULL) return;
	if (vector_ptr->size == 0) return;
}

void sort_tree(tree_node* tree_ptr, alg_compare_priority* func)
{
	if (tree_ptr == NULL || func == NULL) return;

	if (tree_ptr->children == NULL || tree_ptr->children->size == 0) return;

	sort_vector(tree_ptr->children, func);

	for (int i = 0; i < tree_ptr->children->size; i++)
	{
		tree_node* child = tree_node_get_child(tree_ptr, i);
		sort_tree(child, func);
	}
}
