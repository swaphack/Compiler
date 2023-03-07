#pragma once

#include "data/macros.h"
#include "data/string_data.h"

#ifdef __cplusplus
extern "C" {
#endif

// ����ַ��
typedef struct tac
{
	// ������
	string* op;
	void* a;
	void* b;
	void* c;
}tac;

// ����ַ��ת�������
string* tac_to_assembly(tac* tac_ptr);

#ifdef __cplusplus
}

#endif