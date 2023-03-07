#pragma once

#include "data/macros.h"
#include "data/string_data.h"

#ifdef __cplusplus
extern "C" {
#endif

// 三地址码
typedef struct tac
{
	// 操作符
	string* op;
	void* a;
	void* b;
	void* c;
}tac;

// 三地址码转汇编语言
string* tac_to_assembly(tac* tac_ptr);

#ifdef __cplusplus
}

#endif