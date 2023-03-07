#pragma once

#include "data/macros.h"

// 元符号匹配
#ifdef __cplusplus
extern "C" {
#endif

struct string_stream;
struct regex_pattern_meta;
struct regex_pattern_tree;

// ^ 从开始行开始匹配
bool regex_expr_match_start_with(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// $ 从末端开始匹配
bool regex_expr_match_end_with(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// | 或运算符，匹配符号前或后的字符
bool regex_expr_match_or(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// \ 转义字符，用于匹配一些保留的字符 [ ] ( ) { } . * + ? ^ $ \ |
bool regex_expr_match_escape(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// (abc) 字符集，匹配与abc完全相等的字符
bool regex_expr_match_equal_charset(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// {n,m}匹配num个大括号之前的字符或字符集 (n <=num<=m)
bool regex_expr_match_range_count(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// + 匹配>=1个重复+号之前的字符
bool regex_expr_match_gequal_1_count(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// * 匹配>=0个重复*号之前的字符
bool regex_expr_match_gequal_0_count(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// [] 字符种类。匹配方括号内的任意字符
bool regex_expr_match_in_charset(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// [^] 否定字符种类。匹配除了方括号内的任意字符
bool regex_expr_match_notin_charset(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// ? 标记?之前的字符为可选(0个或1个)
bool regex_expr_match_optional(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// . 句号匹配任意当个字符，除了换行符'\r' 'n'
bool regex_expr_match_not_line_break(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// 匹配a-z
bool regex_expr_match_letter_charset_lower(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// 匹配A-Z
bool regex_expr_match_letter_charset_upper(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// 匹配0-9数字
bool regex_expr_match_number_charset(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// 匹配- 连接符
bool regex_expr_match_hyphen_letter(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);
// 匹配, 范围
bool regex_expr_match_hyphen_number(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);

// 匹配非元字符
bool regex_expr_match_no_meta_charset(struct string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);


#ifdef __cplusplus
}

#endif