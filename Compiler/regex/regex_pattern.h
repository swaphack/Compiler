#pragma once

#include "data/string_data.h"
#include "stream/string_stream.h"
#include "collections/stack.h"
#include "collections/tree.h"

// ����ƥ��ģʽ
#ifdef __cplusplus
extern "C" {
#endif

struct regex_meta;
struct regex_meta_table;

// ģʽԪ����
typedef struct regex_pattern_meta
{
	// Ԫ����
	struct regex_meta* meta_ptr;
	// �ַ�
	string* text;
}regex_pattern_meta;


// ģʽ��
typedef struct regex_pattern_tree
{
	// Ԫ���ű� ����
	struct regex_meta_table* rmt_ptr;
	// ģʽ
	string* pattern;
	// �� {data:regex_pattern_meta*}
	tree* meta_tree;
	// �ڵ��ջ {tree_node[data:regex_pattern_meta*]}
	stack* node_stack;
}regex_pattern_tree;

regex_pattern_meta* init_regex_pattern_meta();
void free_regex_pattern_meta(regex_pattern_meta* rpm_ptr);

regex_pattern_tree* init_regex_pattern_tree();
void free_regex_pattern_tree(regex_pattern_tree* rpt_ptr);
void regex_pattern_tree_add_meta(regex_pattern_tree* rpt_ptr, regex_pattern_meta* rpm_ptr);
// ����һ��ջ������
tree_node* regex_pattern_tree_create_stack_node(regex_pattern_tree* rpt_ptr);
// ��ȡջ������
tree_node* regex_pattern_tree_get_stack_node(regex_pattern_tree* rpt_ptr);
// �Ƴ�ջ������
void regex_pattern_tree_pop_stack_node(regex_pattern_tree* rpt_ptr);

// ����Ԫ���� return tree_node{regex_pattern_meta*}
tree_node* regex_pattern_tree_parse_meta(regex_pattern_tree* rpt_ptr, struct string_stream* ss_ptr, struct regex_meta* meta_ptr);

// �������ʽ return tree_node{regex_match*}
tree_node* regex_pattern_tree_parse_expr(regex_pattern_tree* rpt_ptr, struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr);

// �����ڵ�������ȼ�����
void regex_pattern_tree_sort(regex_pattern_tree* rpt_ptr);


int compare_tree_regex_pattern_meta(void* a, void* b);
void del_tree_regex_pattern_meta(void* a);
void del_stack_regex_pattern_meta(void* a);

#ifdef __cplusplus
}

#endif