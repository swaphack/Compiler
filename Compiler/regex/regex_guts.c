#include "regex_guts.h"
#include "data/macros.h"
#include "regex_match.h"
#include "regex_meta.h"


CONSTRUCT_STRUCT(regex_guts);



regex_guts* init_regex_guts()
{
	regex_guts* rg_ptr = create_regex_guts();
	if (rg_ptr == NULL) return NULL;
	rg_ptr->meta_table = init_regex_meta_table();
	regex_meta_table_init(rg_ptr->meta_table);
	rg_ptr->pattern_tree = init_regex_pattern_tree();
	if (rg_ptr->pattern_tree != NULL)
	{
		rg_ptr->pattern_tree->rmt_ptr = rg_ptr->meta_table;
	}
	return rg_ptr;
}

void free_regex_guts(regex_guts* rg_ptr)
{
	if (rg_ptr == NULL) return;
	if (rg_ptr->meta_table != NULL)
	{
		free_regex_meta_table(rg_ptr->meta_table);
		rg_ptr->meta_table = NULL;
	}
	if (rg_ptr->pattern_tree != NULL)
	{
		free_regex_pattern_tree(rg_ptr->pattern_tree);
		rg_ptr->pattern_tree = NULL;
	}
	destroy_regex_guts(rg_ptr);
	rg_ptr = NULL;
}

void regex_guts_comp(regex_guts* rg_ptr, const char* regex)
{
	if (rg_ptr == NULL || regex == NULL) return;

	if (rg_ptr->meta_table == NULL || rg_ptr->pattern_tree == NULL) return;

	regex_meta_table* rmt_ptr = rg_ptr->meta_table;
	regex_pattern_tree* rpt_ptr = rg_ptr->pattern_tree;

	tree_clear(rpt_ptr->meta_tree);

	string* pattern = init_c_string(regex);
	if (pattern == NULL) return;
	rpt_ptr->pattern = pattern;

	regex_pattern_meta* rpm_ptr = init_regex_pattern_meta();
	if (rpm_ptr == NULL) return;
	rpm_ptr->text = clone_string(pattern);

	// 添加根节点
	tree_node* tn_ptr = regex_pattern_tree_create_stack_node(rpt_ptr);
	if (tn_ptr == NULL) return;
	tn_ptr->data = rpm_ptr;
	tree_add_node(rpt_ptr->meta_tree, tn_ptr);

	string_stream* ss_ptr = init_string_stream();
	if (ss_ptr == NULL) return;
	string_stream_init_with(ss_ptr, pattern, 0);
	do
	{
		bool ret = string_stream_is_over(ss_ptr);
		if (ret) break;
		ret = regex_guts_comp_step(rpt_ptr, ss_ptr);
		if (!ret) break;
		string_stream_move_next(ss_ptr);
	} while (true);
	free_string_stream(ss_ptr);

	regex_pattern_tree_pop_stack_node(rpt_ptr);
}

bool regex_guts_comp_step(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr)
{
	if (rpt_ptr == NULL || rpt_ptr->rmt_ptr == NULL || ss_ptr == NULL) return false;
	if (string_stream_is_over(ss_ptr)) return false;

	tree_node* tn_root = regex_pattern_tree_get_stack_node(rpt_ptr);
	if (tn_root == NULL) return false;

	string* expr = init_empty_string();
	char c = string_stream_char_at_cursor(ss_ptr);
	string_append_char(expr, 1, c);

	tree_node* tn_ptr = NULL;
	vector* vector_ptr = regex_meta_table_find_meta_with_string(rpt_ptr->rmt_ptr, expr);
	if (vector_ptr != NULL && vector_ptr->size > 0)
	{
		string* last_start_meta = NULL;
		string* last_meta = NULL;
		int index = -1;
		for (int i = 0; i < vector_ptr->size; i++)
		{
			regex_meta* rm_ptr = (regex_meta*)vector_get_data(vector_ptr, i);
			if (rm_ptr == NULL) continue;
			if (string_is_null_or_empty(rm_ptr->start_meta))
			{
				if (last_meta == NULL
					|| last_meta->size < rm_ptr->meta->size)
				{
					if (string_stream_equal_string(ss_ptr, rm_ptr->meta))
					{
						last_meta = rm_ptr->meta;
						index = i;
					}
					
				}
			}
			else
			{
				if (last_start_meta == NULL
					|| last_start_meta->size < rm_ptr->start_meta->size)
				{
					if (string_stream_equal_string(ss_ptr, rm_ptr->start_meta))
					{
						last_start_meta = rm_ptr->start_meta;
						index = i;
					}
				}
			}
		}

		if (index != -1)
		{
			regex_meta* rm_ptr = (regex_meta*)vector_get_data(vector_ptr, index);
			tn_ptr = regex_pattern_tree_parse_meta(rpt_ptr, ss_ptr, rm_ptr);
		}
	}
	free_string(expr);
	free_vector(vector_ptr);

	if (tn_ptr == NULL)
	{
		regex_meta* rm_ptr = regex_meta_table_get(rpt_ptr->rmt_ptr, init_c_string(REGEX_NO_META));
		if (rm_ptr != NULL)
		{
			tn_ptr = regex_pattern_tree_parse_meta(rpt_ptr, ss_ptr, rm_ptr);
		}
	}

	if (tn_ptr)
	{
		tree_node_add_child(tn_root, tn_ptr);
	}
	

	return tn_ptr != NULL;
}

void regex_guts_sort(regex_guts* rg_ptr)
{
	if (rg_ptr == NULL) return;

	regex_pattern_tree_sort(rg_ptr->pattern_tree);
}

void regex_guts_exec(regex_guts* rg_ptr, const char* expr)
{
	if (rg_ptr == NULL || expr == NULL) return;

	if (rg_ptr->meta_table == NULL || rg_ptr->pattern_tree == NULL) return;

	regex_meta_table* rmt_ptr = rg_ptr->meta_table;
	regex_pattern_tree* rpt_ptr = rg_ptr->pattern_tree;

	string* expression = init_c_string(expr);
	if (expression == NULL) return;
	rg_ptr->expression = expression;

	string_stream* ss_ptr = init_string_stream();
	if (ss_ptr == NULL) return;
	string_stream_init_with(ss_ptr, expression, 0);
	do
	{
		bool ret = string_stream_is_over(ss_ptr);
		if (ret) break;
		ret = regex_guts_exec_step(rpt_ptr, ss_ptr);
		if (!ret) break;
	} while (true);
	free_string_stream(ss_ptr);
	free_string(expression);
}

bool regex_guts_exec_step(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr)
{
	if (rpt_ptr == NULL || rpt_ptr->rmt_ptr == NULL || ss_ptr == NULL) return false;
	if (string_stream_is_over(ss_ptr)) return false;

	if (rpt_ptr->meta_tree == NULL) return false;
	tree_node* tn_ptr = rpt_ptr->meta_tree->root;
	if (tn_ptr == NULL) return false;

	//regex_pattern_meta* rpm_ptr = tn_ptr->data;


	return false;
}
