#pragma once

#include "collections/map.h"
#include "collections/list.h"
#include "data/string_data.h"
#include "stream/string_stream.h"
#include "collections/tree.h"

// 正则表达式 
#ifdef __cplusplus
extern "C" {
#endif
/*
正则表达式从左到右进行计算，并遵循优先级顺序，这与算术表达式非常类似。
相同优先级的从左到右进行运算，不同优先级的运算先高后低
运算符优先级
1、 \									转义符
2、	(), (? : ), (? = ), []				圆括号和方括号
3、 *, +, ? , { n }, { n, }, { n,m }	限定符
4、 ^, $, \任何元字符、任何字符			定位点和序列（即：位置和顺序）	
5、 |									替换，"或"操作 字符具有高于替换运算符的优先级
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

// 非元符号
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

// 正则元符号
typedef struct regex_meta
{
	// 优先级，从1开始，越小优先级越大
	int priority;
	// 元符号
	string* meta;
	// 开始符号
	string* start_meta;
	// 结束符号
	string* end_meta;
	// 元符号匹配
	regex_meta_match* match_meta_ptr;
	// 表达式匹配
	regex_expr_match* match_expr_ptr;
}regex_meta;

// 元符号表
typedef struct regex_meta_table
{
	// 元符号 {string*, regex_meta*}
	map* meta_charset;

}regex_meta_table;


regex_meta* init_regex_meta(int priority, const char* meta, const char* start, const char* end, regex_meta_match* meta_func, regex_expr_match* expr_func);
void free_regex_meta(regex_meta* rm_ptr);

regex_meta_table* init_regex_meta_table();
void regex_meta_table_init(regex_meta_table* rmt_ptr);
void free_regex_meta_table(regex_meta_table* rmt_ptr);

void regex_meta_table_add(regex_meta_table* rmt_ptr, regex_meta* rm_ptr);
regex_meta* regex_meta_table_get(regex_meta_table* rmt_ptr, string* meta);
// 返回值：{regex_meta*}
vector* regex_meta_table_find_meta_with_string(regex_meta_table* rmt_ptr, string* str);

void del_map_regex_meta(void* key, void* value);

#ifdef __cplusplus
}

#endif