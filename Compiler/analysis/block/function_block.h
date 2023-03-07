#pragma once

#include "collections/list.h"
#include "collections/vector.h"
#include "collections/map.h"
#include "data/string_data.h"
#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct variable_block;


// 函数块
typedef struct function_block
{
	// 名称
	string* name;
	// 形参，输入参数 {variable_block}
	vector* input_params;
	// 返回值类型
	string* return_type;
	// 代码
	string* code;
	// 访问权限
	access_type access_type;
	//所属作用域信息
	struct scope_info* scope_info;
}function_block;


function_block* init_function_block();
void free_function_block(function_block* fb_ptr);

// 实参是否与形参匹配
bool function_block_match_input_params(function_block* fb_ptr, struct variable_block** arguments, int count);
// 调用函数
bool function_block_call(function_block* fb_ptr, struct variable_block** arguments, int count, struct variable_block* return_value);
// 代码解析
void function_block_code_parse(function_block* fb_ptr);

void function_block_add_input_param(function_block* fb_ptr, struct variable_block* vb_ptr);
void function_block_remove_input_param(function_block* fb_ptr, string* name);
struct variable_block* function_block_get_input_param(function_block* fb_ptr, string* name);

void del_function_block(void* a);
int compare_function_block(void* a, void* b);
void del_map_string_function_block(void* key, void* value);

#ifdef __cplusplus
}
#endif