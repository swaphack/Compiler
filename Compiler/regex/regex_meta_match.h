#pragma once

#include "data/macros.h"

// Ԫ����ƥ��
#ifdef __cplusplus
extern "C" {
#endif

struct string_stream;
struct regex_meta;
struct regex_pattern_tree;

// ^ �ӿ�ʼ�п�ʼƥ��
bool regex_meta_match_start_with(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// $ ��ĩ�˿�ʼƥ��
bool regex_meta_match_end_with(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// | ���������ƥ�����ǰ�����ַ�
bool regex_meta_match_or(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// \ ת���ַ�������ƥ��һЩ�������ַ� [ ] ( ) { } . * + ? ^ $ \ |
bool regex_meta_match_escape(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// (abc) �ַ�����ƥ����abc��ȫ��ȵ��ַ�
bool regex_meta_match_equal_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// {n,m}ƥ��num��������֮ǰ���ַ����ַ��� (n <=num<=m)
bool regex_meta_match_range_count(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// + ƥ��>=1���ظ�+��֮ǰ���ַ�
bool regex_meta_match_gequal_1_count(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// * ƥ��>=0���ظ�*��֮ǰ���ַ�
bool regex_meta_match_gequal_0_count(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// [] �ַ����ࡣƥ�䷽�����ڵ������ַ�
bool regex_meta_match_in_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// [^] ���ַ����ࡣƥ����˷������ڵ������ַ�
bool regex_meta_match_notin_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// ? ���?֮ǰ���ַ�Ϊ��ѡ(0����1��)
bool regex_meta_match_optional(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// . ���ƥ�����⵱���ַ������˻��з�'\r' 'n'
bool regex_meta_match_not_line_break(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// ƥ��a-z
bool regex_meta_match_letter_charset_lower(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// ƥ��A-Z
bool regex_meta_match_letter_charset_upper(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// ƥ��0-9����
bool regex_meta_match_number_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// ƥ��- ���ӷ�
bool regex_meta_match_hyphen_letter(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
// ƥ��, ��Χ
bool regex_meta_match_hyphen_number(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);

// ƥ���Ԫ�ַ�
bool regex_meta_match_no_meta_charset(struct string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);

#ifdef __cplusplus
}

#endif