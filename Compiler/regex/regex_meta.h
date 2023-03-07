#pragma once

#include "collections/map.h"
#include "collections/list.h"
#include "data/string_data.h"
#include "stream/string_stream.h"
#include "collections/tree.h"

// ������ʽ 
#ifdef __cplusplus
extern "C" {
#endif
/*
������ʽ�����ҽ��м��㣬����ѭ���ȼ�˳�������������ʽ�ǳ����ơ�
��ͬ���ȼ��Ĵ����ҽ������㣬��ͬ���ȼ��������ȸߺ��
��������ȼ�
1�� \									ת���
2��	(), (? : ), (? = ), []				Բ���źͷ�����
3�� *, +, ? , { n }, { n, }, { n,m }	�޶���
4�� ^, $, \�κ�Ԫ�ַ����κ��ַ�			��λ������У�����λ�ú�˳��	
5�� |									�滻��"��"���� �ַ����и����滻����������ȼ�
*/

#define REGEX_META_START_WITH "^"
#define REGEX_META_END_WITH "$"
#define REGEX_META_OR "|"
#define REGEX_META_ESCAPE "\\"

#define REGEX_META_IS_CHARSET "()"
#define REGEX_META_IS_CHARSET_L "("
#define REGEX_META_IS_CHARSET_R ")"

#define REGEX_META_COUNT_RANGE "{}"
#define REGEX_META_COUNT_RANGE_L "{"
#define REGEX_META_COUNT_RANGE_R "}"

#define REGEX_META_GREATER_EQUAL_0 "*"
#define REGEX_META_GREATER_EQUAL_1 "+"

#define REGEX_META_IN_CHARSET "[]"
#define REGEX_META_IN_CHARSET_L "["
#define REGEX_META_IN_CHARSET_R "]"

#define REGEX_META_NOT_IN_CHARSET "[^]"
#define REGEX_META_NOT_IN_CHARSET_L "[^"
#define REGEX_META_NOT_IN_CHARSET_R "]"

#define REGEX_META_OPETIONAL "?"
#define REGEX_META_NOT_LINE_BREAK "."


#define REGEX_IS_META_CHAR(c) (c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}' || \
	c == '.' || c == '*' || c == '+' || c == '?' || c == '^' || c == '$' || c == '\\' || c == '|')

#define REGEX_LOWER_CASE_LETTER "abcdefghijklmnopqrstuvwxyz"
#define REGEX_UPPER_CASE_LETTER "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define REGEX_NUMBER "0123456789"
#define REGEX_HYPHEN_NUMBER ","
#define REGEX_HYPHEN_LETTER "-"

// ��Ԫ����
#define REGEX_NO_META "no_meta"

#define REGEX_IS_LETTER(c) ((c >= 'a' && c <='z') || (c >= 'A' && c <= 'Z'))
#define REGEX_IS_HEXADECIMAL(c) ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
#define REGEX_IS_OCTAL(c) ((c >= '0' && c <='7'))
#define REGEX_IS_NUMBER(c) ((c >= '0' && c <='9'))

struct regex_pattern_tree;
struct regex_meta;
struct regex_pattern_meta;

typedef bool regex_meta_match(string_stream* ss_ptr, struct regex_meta* meta_ptr, struct regex_pattern_tree* tree_ptr);
typedef bool regex_expr_match(string_stream* ss_ptr, struct regex_pattern_meta* rpm_ptr, struct tree_node* tn_ptr);

// ����Ԫ����
typedef struct regex_meta
{
	// ���ȼ�����1��ʼ��ԽС���ȼ�Խ��
	int priority;
	// Ԫ����
	string* meta;
	// ��ʼ����
	string* start_meta;
	// ��������
	string* end_meta;
	// Ԫ����ƥ��
	regex_meta_match* match_meta_ptr;
	// ���ʽƥ��
	regex_expr_match* match_expr_ptr;
}regex_meta;

// Ԫ���ű�
typedef struct regex_meta_table
{
	// Ԫ���� {string*, regex_meta*}
	map* meta_charset;

}regex_meta_table;


regex_meta* init_regex_meta(int priority, const char* meta, const char* start, const char* end, regex_meta_match* meta_func, regex_expr_match* expr_func);
void free_regex_meta(regex_meta* rm_ptr);

regex_meta_table* init_regex_meta_table();
void regex_meta_table_init(regex_meta_table* rmt_ptr);
void free_regex_meta_table(regex_meta_table* rmt_ptr);

void regex_meta_table_add(regex_meta_table* rmt_ptr, regex_meta* rm_ptr);
regex_meta* regex_meta_table_get(regex_meta_table* rmt_ptr, string* meta);
// ����ֵ��{regex_meta*}
vector* regex_meta_table_find_meta_with_string(regex_meta_table* rmt_ptr, string* str);

void del_map_regex_meta(void* key, void* value);

#ifdef __cplusplus
}

#endif