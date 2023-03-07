#pragma once

#include "collections/vector.h"
#include "collections/binary_tree.h"

// 语法分析 syntax analysis
#ifdef __cplusplus
extern "C" {
#endif

// 语法树
typedef struct syntax_tree
{
	// 词法单元结构
	binary_tree* token_tree;
}syntax_tree;


syntax_tree* init_syntax_tree();
void free_syntax_tree(syntax_tree* st_ptr);

#ifdef __cplusplus
}

#endif