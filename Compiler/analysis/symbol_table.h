#pragma once

#include "data/data.h"
#include "data/string_data.h"
#include "collections/vector.h"

#ifdef __cplusplus
extern "C" {
#endif

// 符号
typedef struct symbol_data
{
	// 名称
	hash_string* name;
	// 类型
	string* type;
	// 默认值
	string* value;
}symbol_data;

// 符号表
typedef struct symbol_table
{
	// 符号列表
	vector* sysmbols;
}symbol_table;

symbol_data* init_symbol_data(const char* name);
symbol_data* init_symbol_data_with_type(const char* name, const char* type);
void free_symbol_data(symbol_data* data);

symbol_table* init_symbol_table();
void symbol_table_add_data(symbol_table* st_ptr, symbol_data* data);
void symbol_table_remove_data(symbol_table* st_ptr, const char* name);
int symbol_table_index_of_data(symbol_table* st_ptr, const char* name);
symbol_data* symbol_table_get_data(symbol_table* st_ptr, int index);
symbol_data* symbol_table_find_data(symbol_table* st_ptr, const char* name);
void free_symbol_table(symbol_table* st_ptr);

#ifdef __cplusplus
}
#endif