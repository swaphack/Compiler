#pragma once

#include "collections/map.h"
#include "data/string_data.h"

#ifdef __cplusplus
extern "C" {
#endif

struct variable_block;
struct function_block;
struct struct_block;

// 命名空间体块
typedef struct namespace_block
{
	// 名称
	string* name;
	// 常量 {string*, variable_block*}
	map* const_variables;
	// 静态变量 {string*, variable_block*}
	map* static_variables;
	// 结构体 {string*, struct_block*}
	map* structs;
	// 变量 {string*, variable_block*}
	map* variables;
	// 函数 {string*, function_block*}
	map* functions;
}namespace_block;

namespace_block* init_namespace_block();
void free_namespace_block(namespace_block* nb_ptr);

void namespace_block_add_const_variable(namespace_block* nb_ptr, struct variable_block* vb_ptr);
void namespace_block_remove_const_variable(namespace_block* nb_ptr, string* name);
struct variable_block* namespace_block_get_const_variable(namespace_block* nb_ptr, string* name);

void namespace_block_add_static_variable(namespace_block* nb_ptr, struct variable_block* vb_ptr);
void namespace_block_remove_static_variable(namespace_block* nb_ptr, string* name);
struct variable_block* namespace_block_get_static_variable(namespace_block* nb_ptr, string* name);

void namespace_block_add_variable(namespace_block* nb_ptr, struct variable_block* vb_ptr);
void namespace_block_remove_variable(namespace_block* nb_ptr, string* name);
struct variable_block* namespace_block_get_variable(namespace_block* nb_ptr, string* name);

void namespace_block_add_function(namespace_block* nb_ptr, struct function_block* fb_ptr);
void namespace_block_remove_function(namespace_block* nb_ptr, string* name);
struct function_block* namespace_block_get_function(namespace_block* nb_ptr, string* name);

void namespace_block_add_struct(namespace_block* nb_ptr, struct struct_block* sb_ptr);
void namespace_block_remove_struct(namespace_block* nb_ptr, string* name);
struct function_block* namespace_block_get_struct(namespace_block* nb_ptr, string* name);

#ifdef __cplusplus
}
#endif