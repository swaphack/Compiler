#pragma once

#include "data/string_data.h"
#include "data/string_vector.h"
#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct scope_info;


// 变量块
typedef struct variable_block
{
	// 名称
	string* name;
	// 类型
	string* type;
	// 别名
	vector_string* alias;

	// 默认值
	void* value;
	// 参数传递类型
	delivery_type delivery_type;
	// 访问权限
	access_type access_type;
	//所属作用域信息
	struct scope_info* scope_info;
}variable_block;

variable_block* init_variable_block();
void free_variable_block(variable_block* vb_ptr);

void del_variable_block(void* a);
int compare_variable_block(void* a, void* b);

// map key=string* 
void del_map_string_variable_block(void* key, void* value);

#ifdef __cplusplus
}
#endif