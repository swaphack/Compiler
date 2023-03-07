#pragma once

#include "data/string_data.h"
#include "data/string_vector.h"
#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct scope_info;


// ������
typedef struct variable_block
{
	// ����
	string* name;
	// ����
	string* type;
	// ����
	vector_string* alias;

	// Ĭ��ֵ
	void* value;
	// ������������
	delivery_type delivery_type;
	// ����Ȩ��
	access_type access_type;
	//������������Ϣ
	struct scope_info* scope_info;
}variable_block;

variable_block* init_variable_block();
void free_variable_block(variable_block* vb_ptr);

void del_variable_block(void* a);
int compare_variable_block(void* a, void* b);

// map key=string* 
void del_map_string_variable_block(void* key, void* value);

#ifdef __cplusplus
}
#endif