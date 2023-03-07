#pragma once


#ifdef __cplusplus
extern "C" {
#endif

// 参数传递类型
typedef enum delivery_type
{
	// 值类型
	edt_value,
	// 引用类型
	edt_ref,
}delivery_type;



// 访问权限
typedef enum access_type
{
	eat_public,
	eat_protected,
	eat_internal,
	eat_private,
}access_type;

// 作用域
typedef enum scope_type
{
	// 块
	est_block,
	// 函数
	est_function,
	// 结构体
	est_struct,
	// 命名空间
	est_namespace,
	// 全局
	est_global,
}scope_type;

#ifdef __cplusplus
}
#endif