#pragma once

#include "collections/list.h"
#include "collections/set.h"
#include "data/data.h"
#include "data/string_data.h"
#include "analysis/symbol_table.h"
#include "stream/string_stream.h"

// 词法分析 lexical analysis

#ifdef __cplusplus
extern "C" {
#endif


// 句子
typedef struct lexical_sentence
{
	// 词素 {string*}
	vector* tokens;
	// 文本
	string* text;
}lexical_sentence;

// 块
typedef struct lexical_block
{
	int index;
	// 句子{lexical_sentence*}
	list* sentences;
	// 块{lexical_block*}
	list* blocks;
}lexical_block;


lexical_sentence* init_lexical_sentence();
void free_lexical_sentence(lexical_sentence* ls_ptr);

lexical_block* init_lexical_block();
void free_lexical_block(lexical_block* ll_ptr);

// 是否是数字
bool is_number_string(const string* data);
// 是否是字母
bool is_letter_string(const string* data);
// 是否是变量
bool is_variable_string(const string* data);

#ifdef __cplusplus
}
#endif