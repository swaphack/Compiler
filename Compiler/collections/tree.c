#include "tree.h"
#include "data/macros.h"

CONSTRUCT_STRUCT(tree);
CONSTRUCT_STRUCT(tree_node);
REMOVE_NODE_DATA(tree, tree_node);


int compare_tree_node(void* a, void* b)
{
	tree_node* aa = (tree_node*)a;
	tree_node* bb = (tree_node*)b;

	if (aa->tree == NULL || aa->tree->compare == NULL) return -1;

	int ret =  aa->tree->compare(aa->data, bb->data);
	if (ret != 0) return ret;

	if (aa == bb) return 0;
	return -1;
}
void del_tree_node(void* a)
{
	tree_node* aa = (tree_node*)a;
	free_tree_node(aa);
}

tree_node* init_tree_node(void* data, tree* tree)
{
	tree_node* tn_ptr = create_tree_node();
	tn_ptr->data = data;
	tn_ptr->tree = tree;
	if (tree != NULL)
	{
		tn_ptr->children = init_vector_with_func(compare_tree_node, del_tree_node);
	}
	else
	{
		tn_ptr->children = init_vector();
	}

	return tn_ptr;
}
void free_tree_node(tree_node* tn_ptr)
{
	if (tn_ptr == NULL) return;
	if (tn_ptr->children != NULL)
	{
		free_vector(tn_ptr->children);
		tn_ptr->children = NULL;
	}
	if (tn_ptr->tree != NULL && tn_ptr->tree->del != NULL)
	{
		tn_ptr->tree->del(tn_ptr->data);
	}
	destroy_tree_node(tn_ptr);
}

tree_node* tree_node_find_child(tree_node* tn_ptr, void* data)
{
	if (tn_ptr == NULL || data == NULL) return NULL;
	tree_node temp;
	temp.data = data;
	void* ret = vector_find_data(tn_ptr->children, &temp);
	return (tree_node*)ret;
}
tree_node* tree_node_get_child(tree_node* tn_ptr, int index)
{
	if (tn_ptr == NULL || tn_ptr->children == NULL) return NULL;
	if (index < 0 || index >= tn_ptr->children->size) return NULL;
	return (tree_node*)vector_get_data(tn_ptr->children, index);
}
void tree_node_add_child(tree_node* tn_ptr, tree_node* child)
{
	if (tn_ptr == NULL || child == NULL) return;
	child->tree = tn_ptr->tree;
	child->parent = tn_ptr;
	vector_add_data(tn_ptr->children, child);
}

void tree_node_remove_child_and_cleanup(tree_node* tn_ptr, tree_node* child, bool bcleanup)
{
	if (tn_ptr == NULL || child == NULL) return;
	if (child->parent != tn_ptr) return;
	if (tn_ptr->children == NULL || tn_ptr->children->size == 0) return;

	del_collection_data* ptr = NULL;
	if (!bcleanup)
	{
		ptr = tn_ptr->children->del;
		tn_ptr->children->del = NULL;
	}

	vector_remove_data(tn_ptr->children, child);

	if (!bcleanup)
	{
		tn_ptr->children->del = ptr;
	}
}

void tree_node_remove_child(tree_node* tn_ptr, tree_node* child)
{
	if (tn_ptr == NULL || child == NULL) return;
	if (child->parent != tn_ptr) return;
	if (tn_ptr->children == NULL || tn_ptr->children->size == 0) return;

	vector_remove_data(tn_ptr->children, child);

}
void tree_node_remove_all_children(tree_node* tn_ptr)
{
	if (tn_ptr == NULL) return;

	vector_clear(tn_ptr->children);
}

int tree_node_get_distance_from_root(tree_node* tn_ptr)
{
	if (tn_ptr == NULL) return -1;

	tree_node* tmp = tn_ptr;
	int count = 0;
	while (tmp != NULL)
	{
		count ++;
		tmp = tmp->parent;
	}

	return count - 1;
}

int tree_node_get_index_from_peer(tree_node* tn_ptr)
{
	if (tn_ptr == NULL) return -1;

	if (tn_ptr->parent == NULL) return -1;

	return vector_index_of(tn_ptr->parent->children, tn_ptr);
}

tree* init_tree()
{
	tree* tree_ptr = create_tree();
	return tree_ptr;
}

tree* init_tree_with_func(cmp_collection_data* compare, del_collection_data* del)
{
	tree* tree_ptr = init_tree();
	if (tree_ptr == NULL) return NULL;
	tree_ptr->compare = compare;
	tree_ptr->del = del;
	return tree_ptr;
}

bool tree_contains_data(tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return false;
	if (tree_ptr->compare == NULL) return false;

	tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		return false;
	}

	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
	}

	return false;
}

void* tree_find_data(tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return NULL;
	if (tree_ptr->compare == NULL) return NULL;

	tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		return NULL;
	}
	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret == -1) break;
		if (ret == 0) return node;

		tree_node* child = tree_node_find_child(node, data);
		if (child == NULL) break;
		node = child;
	}
	return NULL;
}

void tree_add_data(tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return;
	if (tree_ptr->compare == NULL) return;

	tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		node = init_tree_node(data, tree_ptr);
		tree_ptr->root = node;
		return;
	}
	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret == -1) break;

		tree_node* child = tree_node_find_child(node, data);
		if (child == NULL)
		{
			tree_node_add_child(node, init_tree_node(data, tree_ptr));
			break;
		}
		else
		{
			node = child;
		}
	}
}


void tree_remove_data(tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return;
	if (tree_ptr->compare == NULL) return;

	tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		node = init_tree_node(data, tree_ptr);
		tree_ptr->root = node;
		return;
	}
	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret == -1) break;

		tree_node* child = tree_node_find_child(node, data);
		if (child == NULL)
		{
			tree_node_remove_child(node, init_tree_node(data, tree_ptr));
			break;
		}
		else
		{
			node = child;
		}
	}
}

void tree_add_node(tree* tree_ptr, tree_node* node_ptr)
{
	if (tree_ptr == NULL || node_ptr == NULL) return;
	if (tree_ptr->compare == NULL) return;

	tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		tree_ptr->root = node_ptr;
		return;
	}
	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, node_ptr->data);
		if (ret == -1) break;

		tree_node* child = tree_node_find_child(node, node_ptr->data);
		if (child == NULL)
		{
			tree_node_add_child(node, node_ptr);
			break;
		}
		else
		{
			node = child;
		}
	}
}

void tree_remove_node(tree* tree_ptr, tree_node* node_ptr)
{
	if (tree_ptr == NULL || node_ptr == NULL) return;

	tree_remove_data(tree_ptr, node_ptr->data);
}

void tree_node_foreach(tree_node* node, foreach_collection_node* func, void* c)
{
	if (node == NULL || func == NULL) return;
	func(node, c);

	for (int i = 0; i < node->children->size; i++)
	{
		tree_node* child_node = (tree_node*)vector_get_data(node->children, i);
		tree_node_foreach(child_node, func, c);
	}
}

void tree_node_foreach_data(tree_node* node, foreach_collection_data* func, void* c)
{
	if (node == NULL || func == NULL) return;
	func(node->data, c);

	for (int i = 0; i < node->children->size; i++)
	{
		tree_node* child_node = (tree_node*)vector_get_data(node->children, i);
		tree_node_foreach_data(child_node, func, c);
	}
}

void* tree_node_find_data(tree_node* node, find_collection_data* func, void* c)
{
	if (node == NULL || func == NULL) return NULL;
	bool ret = func(node->data, c);
	if (ret) return node->data;

	for (int i = 0; i < node->children->size; i++)
	{
		tree_node* child_node = (tree_node*)vector_get_data(node->children, i);
		void* data = tree_node_find_data(child_node, func, c);
		if (data) return data;
	}

	return NULL;
}

void tree_clear(tree* tree_ptr)
{
	if (tree_ptr == NULL || tree_ptr->root == NULL) return;

	free_tree_node(tree_ptr->root);
	tree_ptr->root = NULL;

}

void free_tree(tree* tree_ptr)
{
	if (tree_ptr == NULL || tree_ptr->root == NULL) return;
	free_tree_node(tree_ptr->root);
	tree_ptr->root = NULL;

	tree_ptr = NULL;
}
