#include "alg_convert.h"
#include "collections/vector.h"
#include "collections/tree.h"
#include "collections/queue.h"

tree_node* convert_tree_children_with_priority(struct tree_node* node, alg_get_priority* func)
{
	if (node == NULL) return NULL;
	if (func == NULL) return node;
	if (node->children == NULL || node->children->size == 0) return node;

	int count = node->children->size;
	if (count == 1) return node;

	// вс╫з╣Ц
	queue* peer_queue = init_queue();
	vector* peer_vector = init_vector();
	queue_push_back(peer_queue, peer_vector);

	for (int i = 0; i < count; i++)
	{
		tree_node* child = tree_node_get_child(node, i);
		if (child == NULL) continue;

		vector* peer = (vector*)queue_back(peer_queue);
		if (peer == NULL) break;

		tree_node* back = (tree_node*)vector_get_back(peer);
		if (back == NULL)
		{
			vector_add_data(peer, child);
		}
		else
		{
			int priority = func(child->data);
			int back_priority = func(back->data);
			if (priority > back_priority)
			{
				vector_add_data(peer, child);
			}
			else
			{
				peer_vector = init_vector();
				queue_push_back(peer_queue, peer_vector);
				vector_add_data(peer_vector, child);
			}
		}
	}

	while (!queue_empty(peer_queue))
	{
		vector* vp = queue_peek_front(peer_queue);
		if (vp == NULL || vp->size == 0) continue;

		tree_node* last_node = (tree_node*)vector_get_front(vp);
		if (vp->size > 1)
		{
			for (int i = 1; i < vp->size; i++)
			{
				tree_node* node = (tree_node*)vector_get_data(vp, i);
				if (last_node->parent != NULL)
				{
					tree_node_remove_child_and_cleanup(last_node->parent, last_node, false);
				}
				tree_node_add_child(node, last_node);

				last_node = node;
			}
		}
		free_vector(vp);
	}
	free_queue(peer_queue);

	return node;
}
