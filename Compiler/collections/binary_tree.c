#include "binary_tree.h"

CONSTRUCT_STRUCT(binary_tree);
CONSTRUCT_STRUCT(binary_tree_node);
REMOVE_NODE_DATA(binary_tree, binary_tree_node);

int get_level(binary_tree_node* node, int count)
{
	if (node == NULL)
	{
		return count;
	}

	if (node->left == NULL && node->right == NULL)
	{
		return count;
	}
	int left_level = count;
	int right_level = count;

	if (node->left != NULL)
		left_level = get_level(node->left, count + 1);
	if (node->right != NULL)
		right_level = get_level(node->right, count + 1);

	return left_level > right_level ? left_level : right_level;
}

void binary_tree_free_node(binary_tree* tree_ptr, binary_tree_node* node)
{
	if (tree_ptr != NULL)
	{
		remove_binary_tree_node_data(tree_ptr, node);
	}

	destroy_binary_tree_node(node);
}

binary_tree* init_binary_tree()
{
	binary_tree* tree_ptr = create_binary_tree();
	return tree_ptr;
}

binary_tree* init_binary_tree_with_func(cmp_collection_data* compare, del_collection_data* del)
{
	binary_tree* tree_ptr = init_binary_tree();
	if (tree_ptr == NULL) return NULL;
	tree_ptr->compare = compare;
	tree_ptr->del = del;
	return tree_ptr;
}

bool binary_tree_contains_data(binary_tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return false;
	if (tree_ptr->compare == NULL) return false;

	binary_tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		return false;
	}

	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret > 0)
		{
			node = node->left;
		}
		else if (ret < 0)
		{
			node = node->right;
		}
		else
		{
			return true;
		}
	}

	return false;
}

void* binary_tree_find_data(binary_tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return NULL;
	if (tree_ptr->compare == NULL) return NULL;

	binary_tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		return NULL;
	}

	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret > 0)
		{
			node = node->left;
		}
		else if (ret < 0)
		{
			node = node->right;
		}
		else
		{
			return node->data;
		}
	}

	return NULL;
}

void binary_tree_add_data(binary_tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return;
	if (tree_ptr->compare == NULL) return;

	binary_tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		node = create_binary_tree_node();
		node->data = data;
		tree_ptr->root = node;
		return;
	}

	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret > 0)
		{
			if (node->left != NULL)
			{
				node = node->left;
			}
			else
			{
				binary_tree_node* new_node = create_binary_tree_node();
				new_node->data = data;
				new_node->parent = node;
				node->left = new_node;
				break;
			}
		}
		else if(ret < 0)
		{
			if (node->right != NULL)
			{
				node = node->right;
			}
			else
			{
				binary_tree_node* new_node = create_binary_tree_node();
				new_node->data = data;
				new_node->parent = node;
				node->right = new_node;
				break;
			}
		}
		else
		{
			break;
		}
	}
}

void binary_tree_update_data(binary_tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return;
	if (tree_ptr->compare == NULL) return;

	binary_tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		node = create_binary_tree_node();
		node->data = data;
		tree_ptr->root = node;
		return;
	}

	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret > 0)
		{
			if (node->left != NULL)
			{
				node = node->left;
			}
			else
			{
				binary_tree_node* new_node = create_binary_tree_node();
				new_node->data = data;
				new_node->parent = node;
				node->left = new_node;
				break;
			}
		}
		else if (ret < 0)
		{
			if (node->right != NULL)
			{
				node = node->right;
			}
			else
			{
				binary_tree_node* new_node = create_binary_tree_node();
				new_node->data = data;
				new_node->parent = node;
				node->right = new_node;
				break;
			}
		}
		else
		{
			remove_binary_tree_node_data(tree_ptr, node);
			node->data = data;
			break;
		}
	}
}

void binary_tree_remove_data(binary_tree* tree_ptr, void* data)
{
	if (tree_ptr == NULL || data == NULL) return;
	if (tree_ptr->compare == NULL) return;

	binary_tree_node* node = tree_ptr->root;
	if (node == NULL)
	{
		return;
	}
	while (node != NULL)
	{
		int ret = tree_ptr->compare(node->data, data);
		if (ret > 0)
		{
			if (node->left != NULL)
			{
				node = node->left;
			}
		}
		else if (ret < 0)
		{
			if (node->right != NULL)
			{
				node = node->right;
			}
		}
		else
		{
			binary_tree_node* cur_node_parent = node->parent;
			binary_tree_node* cur_node = node;
			if (node->left == NULL)
			{
				node = node->right;
			}
			else if (node->right == NULL)
			{
				node = node->left;
			}						
			else
			{
				// 判断左右两边，哪个节点的层级多，多的裁剪
				binary_tree_node* node_left = node->left;
				binary_tree_node* node_right = node->right;
				int left_level = get_level(node->left, 0);
				int right_level = get_level(node->right, 0);
				if (left_level >= right_level)
				{// 左边上移,左边取最大值
					binary_tree_node* left_max_node = node_left;
					while (left_max_node != NULL)
					{
						if (left_max_node->right == NULL)
						{
							break;
						}
						left_max_node = left_max_node->right;
					}

					// 修改移位节点的子节点
					if (left_max_node != node_left)
					{
						if (left_max_node->left != NULL)
						{
							left_max_node->left->parent = left_max_node->parent;
							left_max_node->parent->right = left_max_node->left;
						}
					}

					// 替换移位节点到删除节点
					left_max_node->right = cur_node->right;
					if (left_max_node != cur_node->left)
						left_max_node->left = cur_node->left;

					node = left_max_node;
					
				}
				else
				{
					binary_tree_node* right_min_node = node_right;
					while (right_min_node != NULL)
					{
						if (right_min_node->left == NULL)
						{
							break;
						}
						right_min_node = right_min_node->left;
					}
					// 修改移位节点的子节点
					if (right_min_node != node_right)
					{
						if (right_min_node->right != NULL)
						{
							right_min_node->right->parent = right_min_node->parent;
							right_min_node->parent->left = right_min_node->right;
						}
					}
					// 替换移位节点到删除节点
					right_min_node->left = cur_node->left;
					if (right_min_node != cur_node->right)
						right_min_node->right = cur_node->right;

					node = right_min_node;
				}
			}

			if (node != NULL)
			{
				node->parent = cur_node_parent;

				// 父节点
				if (cur_node_parent != NULL)
				{
					if (cur_node == cur_node_parent->left)
					{
						cur_node_parent->left = node;
					}
					else if (cur_node == cur_node_parent->right)
					{
						cur_node_parent->right = node;
					}
				}
				else
				{
					tree_ptr->root = node;
				}
			}

			if (cur_node != NULL)
			{
				binary_tree_free_node(tree_ptr, cur_node);
			}

			break;
		}
	}
}

void binary_tree_node_free(void* a, void* b)
{
	binary_tree_node* node = (binary_tree_node*)a;
	binary_tree* tree_ptr = (binary_tree*)b;

	binary_tree_free_node(tree_ptr, node);
}

void binary_tree_clear(binary_tree* tree_ptr)
{
	if (tree_ptr == NULL) return;
	if (tree_ptr->del != NULL)
	{
		binary_tree_node_foreach_LRD(tree_ptr->root, binary_tree_node_free, tree_ptr);
	}
	tree_ptr->root = NULL;
}

void free_binary_tree(binary_tree* tree_ptr)
{
	if (tree_ptr == NULL) return;
	binary_tree_clear(tree_ptr);
	destroy_binary_tree(tree_ptr);
}

void binary_tree_node_foreach_LDR(binary_tree_node* node, foreach_collection_data* func, void* c)
{
	if (node == NULL || func == NULL) return;

	binary_tree_node_foreach_LDR(node->left, func, c);
	func(node, c);
	binary_tree_node_foreach_LDR(node->right, func, c);
}
void binary_tree_node_foreach_DLR(binary_tree_node* node, foreach_collection_data* func, void* c)
{
	if (node == NULL || func == NULL) return;

	func(node, c);
	binary_tree_node_foreach_DLR(node->left, func, c);
	binary_tree_node_foreach_DLR(node->right, func, c);
}
void binary_tree_node_foreach_LRD(binary_tree_node* node, foreach_collection_data* func, void* c)
{
	if (node == NULL || func == NULL) return;

	binary_tree_node_foreach_LRD(node->left, func, c);
	binary_tree_node_foreach_LRD(node->right, func, c);
	func(node, c);
}

void binary_tree_node_foreach_data_LDR(binary_tree_node* node, foreach_collection_node*func, void* c)
{
	if (node == NULL || func == NULL) return;

	binary_tree_node_foreach_data_LDR(node->left, func, c);
	func(node->data, c);
	binary_tree_node_foreach_data_LDR(node->right, func, c);
}
void binary_tree_node_foreach_data_DLR(binary_tree_node* node, foreach_collection_node*func, void* c)
{
	if (node == NULL || func == NULL) return;

	func(node->data, c);
	binary_tree_node_foreach_data_DLR(node->left, func, c);
	binary_tree_node_foreach_data_DLR(node->right, func, c);
}
void binary_tree_node_foreach_data_LRD(binary_tree_node* node, foreach_collection_node*func, void* c)
{
	if (node == NULL || func == NULL) return;

	binary_tree_node_foreach_data_LRD(node->left, func, c);
	binary_tree_node_foreach_data_LRD(node->right, func, c);
	func(node->data, c);
}

void* binary_tree_node_find_data_DLR(binary_tree_node* node, find_collection_data *func, void* c)
{
	if (node == NULL || node->data == NULL || func == NULL || c == NULL) return NULL;

	bool ret = func(node->data, c);
	if (ret) return node->data;

	void* data = binary_tree_node_find_data_DLR(node->left, func, c);
	if (data != NULL) return data;

	data = binary_tree_node_find_data_DLR(node->right, func, c);
	if (data != NULL) return data;

	return NULL;
}
