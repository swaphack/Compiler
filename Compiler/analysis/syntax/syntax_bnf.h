#pragma once

#include "collections/binary_tree.h"

// 语法 上下文无法文法
#ifdef __cplusplus
extern "C" {
#endif


// 上下文无法文法 bnf 范式
typedef struct syntax_bnf
{
	// 词法单元结构
	binary_tree* token_tree;
}syntax_bnf;


#ifdef __cplusplus
}

#endif