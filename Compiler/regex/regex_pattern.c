#include "regex_pattern.h"
#include "regex_match.h"
#include "regex_meta.h"
#include "data/macros.h"
#include "algorithm/alg_convert.h"
#include <stdio.h>

CONSTRUCT_STRUCT(regex_pattern_meta);
CONSTRUCT_STRUCT(regex_pattern_tree);


int compare_tree_regex_pattern_meta(void* a, void* b)
{
	regex_pattern_meta* aa = (regex_pattern_meta*)a;
	regex_pattern_meta* bb = (regex_pattern_meta*)b;
	if (aa->meta_ptr == NULL || bb->meta_ptr == NULL) return -1;
	string* sa = aa->meta_ptr->meta;
	string* sb = bb->meta_ptr->meta;
	int index = string_first_index(sa, sb->value, sb->size);
	if (index == -1) return -1;
	if (index == 0 && sa->size == sb->size) return 0;
	return 1;
}
void del_tree_regex_pattern_meta(void* a)
{
	regex_pattern_meta* aa = (regex_pattern_meta*)a;
	free_regex_pattern_meta(aa);
}

void del_stack_regex_pattern_meta(void* a)
{
	//regex_pattern_meta* aa = (regex_pattern_meta*)a;
	//free_regex_pattern_meta(aa);
}

regex_pattern_meta* init_regex_pattern_meta()
{
	regex_pattern_meta* rpm_ptr = create_regex_pattern_meta();
	return rpm_ptr;
}
void free_regex_pattern_meta(regex_pattern_meta* rpm_ptr)
{
	if (rpm_ptr == NULL) return;
	if (rpm_ptr->text != NULL)
	{
		free_string(rpm_ptr->text);
		rpm_ptr->text = NULL;
	}
	destroy_regex_pattern_meta(rpm_ptr);
	rpm_ptr = NULL;
}

regex_pattern_tree* init_regex_pattern_tree()
{
	regex_pattern_tree* rpt_ptr = create_regex_pattern_tree();
	if (rpt_ptr == NULL) return NULL;
	rpt_ptr->meta_tree = init_tree_with_func(compare_tree_regex_pattern_meta, del_tree_regex_pattern_meta);
	rpt_ptr->node_stack = init_stack_with_func(del_stack_regex_pattern_meta);
	return rpt_ptr;
}
void free_regex_pattern_tree(regex_pattern_tree* rpt_ptr)
{
	if (rpt_ptr == NULL) return;
	free_string(rpt_ptr->pattern);
	if (rpt_ptr->meta_tree != NULL)
	{
		free_tree(rpt_ptr->meta_tree);
		rpt_ptr->meta_tree = NULL;
	}
	if (rpt_ptr->node_stack != NULL)
	{
		free_stack(rpt_ptr->node_stack);
		rpt_ptr->node_stack = NULL;
	}
	destroy_regex_pattern_tree(rpt_ptr);
}

void regex_pattern_tree_add_meta(regex_pattern_tree* rpt_ptr, regex_pattern_meta* rpm_ptr)
{
	if (rpt_ptr == NULL || rpm_ptr == NULL)
	{
		return;
	}

	tree_add_data(rpt_ptr->meta_tree, rpm_ptr);
}

tree_node* regex_pattern_tree_create_stack_node(regex_pattern_tree* rpt_ptr)
{
	if (rpt_ptr == NULL) return NULL;
	tree_node* tn_ptr = init_tree_node(NULL, rpt_ptr->meta_tree);
	if (tn_ptr == NULL) return NULL;
	stack_push(rpt_ptr->node_stack, tn_ptr);
	return tn_ptr;
}

tree_node* regex_pattern_tree_get_stack_node(regex_pattern_tree* rpt_ptr)
{
	if (rpt_ptr == NULL || rpt_ptr->node_stack == NULL) return NULL;
	tree_node* tn_ptr = (tree_node*)stack_top(rpt_ptr->node_stack);
	return tn_ptr;
}

void regex_pattern_tree_pop_stack_node(regex_pattern_tree* rpt_ptr)
{
	if (rpt_ptr == NULL || rpt_ptr->node_stack == NULL) return;
	stack_pop(rpt_ptr->node_stack);
}

tree_node* regex_pattern_tree_parse_meta(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr, regex_meta* meta_ptr)
{
	if (rpt_ptr == NULL || ss_ptr == NULL || meta_ptr == NULL) return NULL;
	if (string_stream_is_over(ss_ptr)) return NULL;
	if (meta_ptr->match_meta_ptr == NULL) return NULL;


	tree_node* tn_ptr = regex_pattern_tree_create_stack_node(rpt_ptr);
	if (tn_ptr == NULL) return NULL;

	int begin = ss_ptr->cursor;
	bool ret = meta_ptr->match_meta_ptr(ss_ptr, meta_ptr, rpt_ptr);
	if (!ret)
	{
		free_tree_node(tn_ptr);
		regex_pattern_tree_pop_stack_node(rpt_ptr);
		return NULL;
	}
	regex_pattern_meta* rpm_ptr = init_regex_pattern_meta();
	if (rpm_ptr == NULL)
	{
		free_tree_node(tn_ptr);
		regex_pattern_tree_pop_stack_node(rpt_ptr);
		return NULL;
	}
	//string_stream_move_next(ss_ptr);
	int end = ss_ptr->cursor;
	rpm_ptr->meta_ptr = meta_ptr;
	rpm_ptr->text = sub_string_stream(ss_ptr, begin, end - begin + 1);
	tn_ptr->data = rpm_ptr;

	printf("text : %s\n", rpm_ptr->text->value);

	regex_pattern_tree_pop_stack_node(rpt_ptr);

	return tn_ptr;
}

tree_node* regex_pattern_tree_parse_expr(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr, regex_pattern_meta* rpm_ptr)
{
	if (rpt_ptr == NULL || ss_ptr == NULL || rpm_ptr == NULL) return NULL;
	if (string_stream_is_over(ss_ptr)) return NULL;
	if (rpt_ptr->meta_tree == NULL || rpt_ptr->meta_tree->root == NULL) return NULL;

	regex_meta* meta_ptr = rpm_ptr->meta_ptr;
	if (meta_ptr == NULL) return NULL;
	if (meta_ptr->match_expr_ptr == NULL) return NULL;

	tree_node* tn_ptr = regex_pattern_tree_create_stack_node(rpt_ptr);
	if (tn_ptr == NULL) return NULL;

	int begin = ss_ptr->cursor;
	tree_node* root = rpt_ptr->meta_tree->root;
	tree_find_data
	bool ret = meta_ptr->match_expr_ptr(ss_ptr, rpm_ptr, rpt_ptr->meta_tree->root);
	if (!ret)
	{
		free_tree_node(tn_ptr);
		regex_pattern_tree_pop_stack_node(rpt_ptr);
		return NULL;
	}
	regex_match* rm_ptr = init_regex_match();
	if (rpm_ptr == NULL)
	{
		free_tree_node(tn_ptr);
		regex_pattern_tree_pop_stack_node(rpt_ptr);
		return NULL;
	}
	//string_stream_move_next(ss_ptr);
	int end = ss_ptr->cursor;
	rm_ptr->meta_ptr = meta_ptr;
	rm_ptr->begin = begin;
	rm_ptr->end = end;
	tn_ptr->data = rpm_ptr;

	regex_pattern_tree_pop_stack_node(rpt_ptr);

	return tn_ptr;
}

// 正则表达式从左到右进行计算，并遵循优先级顺序，这与算术表达式非常类似。
// 相同优先级的从左到右进行运算，不同优先级的运算先高后低
int get_meta_priority(void* a)
{
	regex_pattern_meta* aa = (regex_pattern_meta*)a;
	if (aa->meta_ptr == NULL) return -1;
	//printf("meta %s, text %s \n", aa->meta_ptr->meta->value, aa->text->value);
	return 100 - aa->meta_ptr->priority;
}

void regex_pattern_tree_sort(regex_pattern_tree* rpt_ptr)
{
	if (rpt_ptr == NULL) return;

	if (rpt_ptr->meta_tree == NULL) return;
	if (rpt_ptr->meta_tree->root == NULL) return;

	tree_node* root = rpt_ptr->meta_tree->root;

	convert_tree_children_with_priority(root, get_meta_priority);
}
