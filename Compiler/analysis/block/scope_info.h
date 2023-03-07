#pragma once

#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

// 作用域信息
typedef struct scope_info
{
	// 作用域类型
	scope_type type;
	// 所属作用域
	void* scope;
}scope_info;

scope_info* init_scope_info();
void scope_info_init_with(scope_info* si_ptr, scope_type type, void* scope);
void free_scope_info(scope_info* si_ptr);


#ifdef __cplusplus
}
#endif