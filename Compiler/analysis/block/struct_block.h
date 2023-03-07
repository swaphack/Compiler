#pragma once

#include "collections/list.h"
#include "collections/vector.h"
#include "collections/map.h"
#include "data/string_data.h"
#include "data/string_vector.h"
#include "analysis/symbol_table.h"
#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct scope_info;
struct variable_block;

// 结构继承
typedef struct struct_inherit
{
	// 访问权限
	access_type access_type;
	// 父类
	struct struct_block* parent;
}struct_inherit;

// 结构体块
typedef struct struct_block
{
	// 名称
	string* name;
	// 常量 {string*, variable_block*}
	map* const_variables;
	// 静态变量 {string*, variable_block*}
	map* static_variables; 
	
	// 变量 {string*, variable_block*}
	map* variables;
	// 函数 {string*, function_block*}
	map* functions;

	// 访问权限
	access_type access_type;
	// 继承
	struct_inherit* inherit;

	//所属作用域信息
	struct scope_info* scope_info;
}struct_block;


/////////////////////////////////////////////////////////
struct_block* init_struct_block();

void struct_block_add_const_variable(struct_block* sb_ptr, struct variable_block* vb_ptr);
void struct_block_remove_const_variable(struct_block* sb_ptr, string* name);
struct variable_block* struct_block_get_const_variable(struct_block* sb_ptr, string* name);

void struct_block_add_static_variable(struct_block* sb_ptr, struct variable_block* vb_ptr);
void struct_block_remove_static_variable(struct_block* sb_ptr, string* name);
struct variable_block* struct_block_get_static_variable(struct_block* sb_ptr, string* name);

void struct_block_add_variable(struct_block* sb_ptr, struct variable_block* vb_ptr);
void struct_block_remove_variable(struct_block* sb_ptr, string* name);
struct variable_block* struct_block_get_variable(struct_block* sb_ptr, string* name);

void struct_block_add_function(struct_block* sb_ptr, struct function_block* fb_ptr);
void struct_block_remove_function(struct_block* sb_ptr, string* name);
struct function_block* struct_block_get_function(struct_block* sb_ptr, string* name);

void free_struct_block(struct_block* sb_ptr);



/////////////////////////////////////////////////////////
// map key=string* 
void del_map_string_struct_block(void* key, void* value);


#ifdef __cplusplus
}
#endif