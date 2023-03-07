#include "regex.h"
#include "data/macros.h"
#include "regex_guts.h"
#include <stdio.h>

CONSTRUCT_STRUCT(regex);

regex* init_regex()
{
	regex* re = create_regex();
	if (re == NULL) return NULL;
	re->re_g = init_regex_guts();
	return re;
}

size_t regex_error(int errcode, const regex* preg, char* errbuf, size_t errbuf_size)
{
	return 0;
}

void show_tree_regex_pattern_meta(void* a, void* b)
{
	tree_node* node = (tree_node*)a;

	int lv = tree_node_get_distance_from_root(node);
	int index = tree_node_get_index_from_peer(node);
	printf("(%d, %d) ", lv, index);
	regex_pattern_meta* aa = (regex_pattern_meta*)node->data;
	if (aa->meta_ptr != NULL)
	{
		printf("pattern meta : %s ", aa->meta_ptr->meta->value);
	}
	printf("match text : %s\n", aa->text->value);
}

int regex_comp(regex* preg, const char* regex, int cflags)
{
	if (preg == NULL || regex == NULL) return -1;

	regex_guts_comp(preg->re_g, regex);

	if (preg->re_g->pattern_tree == NULL) return -1;
	regex_pattern_tree* rpt_ptr = preg->re_g->pattern_tree;
	if (rpt_ptr->meta_tree == NULL || rpt_ptr->meta_tree->root == NULL) return -1;

	tree_node_foreach(rpt_ptr->meta_tree->root, show_tree_regex_pattern_meta, NULL);

	regex_guts_sort(preg->re_g);

	tree_node_foreach(rpt_ptr->meta_tree->root, show_tree_regex_pattern_meta, NULL);

	return 0;
}
int regex_exec(const regex* preg, const char* expr, size_t nmatch, regmatch pmatch[], int eflags)
{
	if (preg == NULL || expr == NULL || pmatch == NULL) return -1;

	regex_guts_exec(preg->re_g, expr);

	return 0;
}
void free_regex(regex* re)
{
	if (re == NULL) return;
	if (re != NULL)
	{
		free_regex_guts(re->re_g);
		re->re_g = NULL;
	}
	destroy_regex(re);
	re = NULL;
}