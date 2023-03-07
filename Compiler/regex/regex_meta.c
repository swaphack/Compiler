#include "regex_meta.h"
#include "data/macros.h"
#include "collections/extensions.h"
#include "regex_match.h"
#include "regex_pattern.h"
#include "regex_guts.h"
#include "regex_meta_match.h"
#include "regex_expr_match.h"

CONSTRUCT_STRUCT(regex_meta);
CONSTRUCT_STRUCT(regex_meta_table);

regex_meta* init_regex_meta(int priority, const char* meta, const char* start, const char* end, regex_meta_match* meta_func, regex_expr_match* expr_func)
{
	regex_meta* rm_ptr = create_regex_meta();
	if (rm_ptr == NULL) return NULL;
	rm_ptr->priority = priority;
	rm_ptr->meta = init_c_string(meta);
	rm_ptr->start_meta = init_c_string(start);
	rm_ptr->end_meta = init_c_string(end);
	rm_ptr->match_meta_ptr = meta_func;
	rm_ptr->match_expr_ptr = expr_func;
	return rm_ptr;
}

void free_regex_meta(regex_meta* rm_ptr)
{
	if (rm_ptr == NULL) return;
	if (rm_ptr->meta)
	{
		free_string(rm_ptr->meta);
		rm_ptr->meta = NULL;
	}
	if (rm_ptr->start_meta)
	{
		free_string(rm_ptr->start_meta);
		rm_ptr->start_meta = NULL;
	}
	if (rm_ptr->end_meta)
	{
		free_string(rm_ptr->end_meta);
		rm_ptr->end_meta = NULL;
	}
	destroy_regex_meta(rm_ptr);
	rm_ptr = NULL;
}

void del_map_regex_meta(void* key, void* value)
{
	string* a = (string*)key;
	regex_meta* b = (regex_meta*)value;

	free_string(a);
	free_regex_meta(b);
}

regex_meta_table* init_regex_meta_table()
{
	regex_meta_table* rmt_ptr = create_regex_meta_table();
	if (rmt_ptr == NULL) return NULL;
	rmt_ptr->meta_charset = init_map_with_string_key(del_map_regex_meta);
	return rmt_ptr;
}

#define ADD_REGEX_META(tbl, lv, a, b, c, f1, f2)\
{\
regex_meta* rm_ptr = init_regex_meta(lv, a, b, c, f1, f2);\
if (rm_ptr != NULL) map_add_data(tbl, init_c_string(a), rm_ptr);\
}

void regex_meta_table_init(regex_meta_table* rmt_ptr)
{
	if (rmt_ptr == NULL) return;

	map* tbl = rmt_ptr->meta_charset;
	if (tbl == NULL) return;

	ADD_REGEX_META(tbl, 4, REGEX_META_START_WITH, NULL, NULL, regex_meta_match_start_with, regex_expr_match_start_with);
	ADD_REGEX_META(tbl, 4, REGEX_META_END_WITH, NULL, NULL, regex_meta_match_end_with, regex_expr_match_end_with);
	ADD_REGEX_META(tbl, 6, REGEX_META_OR, NULL, NULL, regex_meta_match_or, regex_expr_match_or);
	ADD_REGEX_META(tbl, 1, REGEX_META_ESCAPE, NULL, NULL, regex_meta_match_escape, regex_expr_match_escape);
	ADD_REGEX_META(tbl, 2, REGEX_META_IS_CHARSET, REGEX_META_IS_CHARSET_L, REGEX_META_IS_CHARSET_R, regex_meta_match_equal_charset, regex_expr_match_equal_charset);
	ADD_REGEX_META(tbl, 3, REGEX_META_COUNT_RANGE, REGEX_META_COUNT_RANGE_L, REGEX_META_COUNT_RANGE_R, regex_meta_match_range_count, regex_expr_match_range_count);
	ADD_REGEX_META(tbl, 3, REGEX_META_GREATER_EQUAL_0, NULL, NULL, regex_meta_match_gequal_1_count, regex_expr_match_gequal_1_count);
	ADD_REGEX_META(tbl, 3, REGEX_META_GREATER_EQUAL_1, NULL, NULL, regex_meta_match_gequal_0_count, regex_expr_match_gequal_0_count);

	ADD_REGEX_META(tbl, 2, REGEX_META_IN_CHARSET, REGEX_META_IN_CHARSET_L, REGEX_META_IN_CHARSET_R, regex_meta_match_in_charset, regex_expr_match_in_charset);
	ADD_REGEX_META(tbl, 2, REGEX_META_NOT_IN_CHARSET, REGEX_META_NOT_IN_CHARSET_L, REGEX_META_NOT_IN_CHARSET_R, regex_meta_match_notin_charset, regex_expr_match_notin_charset);

	ADD_REGEX_META(tbl, 3, REGEX_META_OPETIONAL, NULL, NULL, regex_meta_match_optional, regex_expr_match_optional);
	ADD_REGEX_META(tbl, 4, REGEX_META_NOT_LINE_BREAK, NULL, NULL, regex_meta_match_not_line_break, regex_expr_match_not_line_break);
	ADD_REGEX_META(tbl, 5, REGEX_NO_META, NULL, NULL, regex_meta_match_no_meta_charset, regex_expr_match_no_meta_charset);
}

void free_regex_meta_table(regex_meta_table* rmt_ptr)
{
	if (rmt_ptr == NULL) return;
	if (rmt_ptr->meta_charset != NULL)
	{
		free_map(rmt_ptr->meta_charset);
		rmt_ptr->meta_charset = NULL;
	}

	destroy_regex_meta_table(rmt_ptr);
	rmt_ptr = NULL;
}

void regex_meta_table_add(regex_meta_table* rmt_ptr, regex_meta* rm_ptr)
{
	if (rmt_ptr == NULL || rm_ptr == NULL) return;
	if (rmt_ptr->meta_charset == NULL) return;

	string* key = clone_string(rm_ptr->meta);
	map_add_data(rmt_ptr->meta_charset, key, rm_ptr);
}

regex_meta* regex_meta_table_get(regex_meta_table* rmt_ptr, string* meta)
{
	if (rmt_ptr == NULL || meta == NULL) return NULL;

	return (regex_meta*)map_get_value(rmt_ptr->meta_charset, meta);
}

typedef struct meta_table_result
{
	// 搜索结果集合{regex_meta*}
	vector* vptr;
	// 待查找文本
	string* text;
}meta_table_result;

void map_foreach_regex_meta(void* a, void* b)
{
	regex_meta* aa = (regex_meta*)a;
	meta_table_result* bb = (meta_table_result*)b;
	string* txt = bb->text;
	int index = string_first_index(aa->meta, txt->value, txt->size);
	if (index != -1)
	{
		vector_add_data(bb->vptr, aa);
	}
}

vector* regex_meta_table_find_meta_with_string(regex_meta_table* rmt_ptr, string* str)
{
	if (rmt_ptr == NULL || str == NULL) return NULL;

	vector* vptr = init_vector();
	meta_table_result ret;
	ret.vptr = vptr;
	ret.text = str;

	map_foreach_value(rmt_ptr->meta_charset, map_foreach_regex_meta, &ret);
	return vptr;
}




