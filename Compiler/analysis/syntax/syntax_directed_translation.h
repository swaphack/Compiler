#pragma once

#include "collections/binary_tree.h"

// �﷨�Ƶ�����
#ifdef __cplusplus
extern "C" {
#endif


// bnf ��ʽ
typedef struct syntax_directed_translation
{
	// �ʷ���Ԫ�ṹ
	binary_tree* token_tree;
}syntax_directed_translation;


#ifdef __cplusplus
}

#endif