#pragma once

#include "collections/binary_tree.h"

// �﷨ �������޷��ķ�
#ifdef __cplusplus
extern "C" {
#endif


// �������޷��ķ� bnf ��ʽ
typedef struct syntax_bnf
{
	// �ʷ���Ԫ�ṹ
	binary_tree* token_tree;
}syntax_bnf;


#ifdef __cplusplus
}

#endif