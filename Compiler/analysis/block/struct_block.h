#pragma once

#include "collections/list.h"
#include "collections/vector.h"
#include "collections/map.h"
#include "data/string_data.h"
#include "data/string_vector.h"
#include "analysis/symbol_table.h"
#include "marcros.h"

#ifdef __cplusplus
extern "C" {
#endif

struct scope_info;
struct variable_block;

// �ṹ�̳�
typedef struct struct_inherit
{
	// ����Ȩ��
	access_type access_type;
	// ����
	struct struct_block* parent;
}struct_inherit;

// �ṹ���
typedef struct struct_block
{
	// ����
	string* name;
	// ���� {string*, variable_block*}
	map* const_variables;
	// ��̬���� {string*, variable_block*}
	map* static_variables; 
	
	// ���� {string*, variable_block*}
	map* variables;
	// ���� {string*, function_block*}
	map* functions;

	// ����Ȩ��
	access_type access_type;
	// �̳�
	struct_inherit* inherit;

	//������������Ϣ
	struct scope_info* scope_info;
}struct_block;


/////////////////////////////////////////////////////////
struct_block* init_struct_block();

void struct_block_add_const_variable(struct_block* sb_ptr, struct variable_block* vb_ptr);
void struct_block_remove_const_variable(struct_block* sb_ptr, string* name);
struct variable_block* struct_block_get_const_variable(struct_block* sb_ptr, string* name);

void struct_block_add_static_variable(struct_block* sb_ptr, struct variable_block* vb_ptr);
void struct_block_remove_static_variable(struct_block* sb_ptr, string* name);
struct variable_block* struct_block_get_static_variable(struct_block* sb_ptr, string* name);

void struct_block_add_variable(struct_block* sb_ptr, struct variable_block* vb_ptr);
void struct_block_remove_variable(struct_block* sb_ptr, string* name);
struct variable_block* struct_block_get_variable(struct_block* sb_ptr, string* name);

void struct_block_add_function(struct_block* sb_ptr, struct function_block* fb_ptr);
void struct_block_remove_function(struct_block* sb_ptr, string* name);
struct function_block* struct_block_get_function(struct_block* sb_ptr, string* name);

void free_struct_block(struct_block* sb_ptr);



/////////////////////////////////////////////////////////
// map key=string* 
void del_map_string_struct_block(void* key, void* value);


#ifdef __cplusplus
}
#endif