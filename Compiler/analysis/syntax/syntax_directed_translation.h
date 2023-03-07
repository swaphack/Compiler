#pragma once

#include "collections/binary_tree.h"

// 语法制导翻译
#ifdef __cplusplus
extern "C" {
#endif


// bnf 范式
typedef struct syntax_directed_translation
{
	// 词法单元结构
	binary_tree* token_tree;
}syntax_directed_translation;


#ifdef __cplusplus
}

#endif