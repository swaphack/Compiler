#pragma once

#include "symbol_table.h"
#include "collections/map.h"
#include "collections/list.h"
#ifdef __cplusplus
extern "C" {
#endif

#define TABLE_PREPROCESS_ID "preprocess"
#define TABLE_KEY_NAME "key"
#define TABLE_SYMBOL_NAME "symbol"
#define TABLE_FUNCTION_NAME "function"
#define TABLE_STRUCT_NAME "struct"

// 词法表
typedef enum lexical_table_type
{
	// 预处理表
	eltt_preprocess,
	// 符号表
	eltt_symbol,
	// 关键字表
	eltt_key,
	// 函数表
	eltt_function,
	// 类型表
	eltt_struct,
	// 块表
	eltt_block,
}lexical_table_type;

// 词法单元
typedef struct lexical_token
{
	// 名称 词素
	hash_string* name;
	// sysmbol_table 索引
	int sysmbol_index;
	// 表字段名称
	string* lt_name;
	// 表类型
	lexical_table_type table_type;
}lexical_token;

// 词法分析 lexical analysis
typedef struct analysis_table
{
	// 预处理表
	symbol_table* preprocess_table;
	// 符号表
	symbol_table* sign_table;
	// 关键字表
	symbol_table* key_table;
	// 类型表
	symbol_table* struct_table;
	// 函数表
	symbol_table* function_table;
	// 块表 [ ] {} ()
	map* block_table;
	// 无用符号表 {string*}
	list* invalid_table;
}analysis_table;

analysis_table* init_analysis_table();
void free_analysis_table(analysis_table* at_ptr);

//词素索引 type : lexical_table_type
int lexical_analysis_token_index(analysis_table* at_ptr, string* str, int* type);
// 创建词素 type : lexical_table_type
struct lexical_token* lexical_analysis_create_token(analysis_table* at_ptr, int type, int index, string* str);


#ifdef __cplusplus
}
#endif