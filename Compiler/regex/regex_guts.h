#pragma once

#include "data/string_data.h"
#include "regex_meta.h"
#include "regex_pattern.h"

#ifdef __cplusplus
extern "C" {
#endif

// ƥ����ʽ
typedef struct regex_guts
{
	// Ԫ���ű�
	struct regex_meta_table* meta_table;
	// ģʽ��
	regex_pattern_tree* pattern_tree;
	// ʽ��
	string* expression;
}regex_guts;

regex_guts* init_regex_guts();
void free_regex_guts(regex_guts* rg_ptr);

// ����ģʽ
void regex_guts_comp(regex_guts* rg_ptr, const char* pattern);
bool regex_guts_comp_step(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr);

// ���ȼ�����
void regex_guts_sort(regex_guts* rg_ptr);

// �������ʽ
void regex_guts_exec(regex_guts* rg_ptr, const char* expr);
bool regex_guts_exec_step(regex_pattern_tree* rpt_ptr, string_stream* ss_ptr);

#ifdef __cplusplus
}

#endif