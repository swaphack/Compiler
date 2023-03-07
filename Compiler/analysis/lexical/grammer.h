#pragma once

// 文法

#ifdef __cplusplus
extern "C" {
#endif

struct string;
struct analysis_table;

// 是否是终结符 关键字，符号
bool is_terminal_word(const struct string* word, struct analysis_table* st_ptr);
// 是否非终结符 类型表和函数表名称
bool is_nonterminal_word(const struct string* word, struct analysis_table* st_ptr);


#ifdef __cplusplus
}
#endif