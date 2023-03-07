#pragma once

#include "data/string_data.h"
#include "stream/string_stream.h"
#include "collections/stack.h"
#include "collections/tree.h"

// 正则匹配模式
#ifdef __cplusplus
extern "C" {
#endif

struct regex_meta;
struct regex_meta_table;

// 模式元数据
typedef struct regex_pattern_meta
{
	// 元符号
	struct regex_meta* meta_ptr;
	// 字符
	string* text;
}regex_pattern_meta;


// 模式树
typedef struct regex_pattern_tree
{
	// 元符号表 引用
	struct regex_meta_table* rmt_ptr;
	// 模式
	string* pattern;
	// 树 {data:regex_pattern_meta*}
	tree* meta_tree;
	// 节点堆栈 {tree_node[data:regex_pattern_meta*]}
	stack* node_stack;
}regex_pattern_tree;

regex_pattern_meta* init_regex_pattern_meta();
void free_regex_pattern_meta(regex_pattern_meta* rpm_ptr);

regex_pattern_tree* init_regex_pattern_tree();
void free_regex_pattern_tree(regex_pattern_tree* rpt_ptr);
void regex_pattern_tree_add_meta(regex_pattern_tree* rpt_ptr, regex_pattern_meta* rpm_ptr);
// 创建一个栈顶数据
tree_node* regex_pattern_tree_create_stack_node(regex_pattern_tree* rpt_ptr);
// 获取栈顶数据
tree_node* regex_pattern_tree_get_stack_node(regex_pattern_tree* rpt_ptr);
// 移除栈顶数据
void regex_pattern_tree_pop_stack_node(regex_pattern_tree* rpt_ptr);

// 解析元符号 return tree_node{regex_pattern_meta*}
tree_node* regex_pattern_tree_parse_meta(regex_pattern_tree* rpt_ptr, struct string_stream* ss_ptr, struct regex_meta* meta_ptr);

// 解析表达式 return tree_node{regex_match*}
tree_node* regex_pattern_tree_parse_expr(regex_pattern_tree* rpt_ptr, struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr);

// 对树节点进行优先级排序
void regex_pattern_tree_sort(regex_pattern_tree* rpt_ptr);


int compare_tree_regex_pattern_meta(void* a, void* b);
void del_tree_regex_pattern_meta(void* a);
void del_stack_regex_pattern_meta(void* a);

#ifdef __cplusplus
}

#endif