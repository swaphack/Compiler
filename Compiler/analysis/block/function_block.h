#pragma once

#include "collections/list.h"
#include "collections/vector.h"
#include "collections/map.h"
#include "data/string_data.h"
#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct variable_block;


// ������
typedef struct function_block
{
	// ����
	string* name;
	// �βΣ�������� {variable_block}
	vector* input_params;
	// ����ֵ����
	string* return_type;
	// ����
	string* code;
	// ����Ȩ��
	access_type access_type;
	//������������Ϣ
	struct scope_info* scope_info;
}function_block;


function_block* init_function_block();
void free_function_block(function_block* fb_ptr);

// ʵ���Ƿ����β�ƥ��
bool function_block_match_input_params(function_block* fb_ptr, struct variable_block** arguments, int count);
// ���ú���
bool function_block_call(function_block* fb_ptr, struct variable_block** arguments, int count, struct variable_block* return_value);
// �������
void function_block_code_parse(function_block* fb_ptr);

void function_block_add_input_param(function_block* fb_ptr, struct variable_block* vb_ptr);
void function_block_remove_input_param(function_block* fb_ptr, string* name);
struct variable_block* function_block_get_input_param(function_block* fb_ptr, string* name);

void del_function_block(void* a);
int compare_function_block(void* a, void* b);
void del_map_string_function_block(void* key, void* value);

#ifdef __cplusplus
}
#endif