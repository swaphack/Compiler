#pragma once

#include "data/string_data.h"
#include "regex_meta.h"
#include "regex_pattern.h"

#ifdef __cplusplus
extern "C" {
#endif

// 匹配表达式
typedef struct regex_guts
{
	// 元符号表
	struct regex_meta_table* meta_table;
	// 模式树
	regex_pattern_tree* pattern_tree;
	// 式子
	string* expression;
}regex_guts;

regex_guts* init_regex_guts();
void free_regex_guts(regex_guts* rg_ptr);

// 编译模式
void regex_guts_comp(regex_guts* rg_ptr, const char* pattern);
bool regex_guts_comp_step(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr);

// 优先级排序
void regex_guts_sort(regex_guts* rg_ptr);

// 解析表达式
void regex_guts_exec(regex_guts* rg_ptr, const char* expr);
bool regex_guts_exec_step(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr);

#ifdef __cplusplus
}

#endif