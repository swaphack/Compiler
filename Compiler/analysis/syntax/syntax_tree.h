#pragma once

#include "collections/vector.h"
#include "collections/binary_tree.h"

// �﷨���� syntax analysis
#ifdef __cplusplus
extern "C" {
#endif

// �﷨��
typedef struct syntax_tree
{
	// �ʷ���Ԫ�ṹ
	binary_tree* token_tree;
}syntax_tree;


syntax_tree* init_syntax_tree();
void free_syntax_tree(syntax_tree* st_ptr);

#ifdef __cplusplus
}

#endif