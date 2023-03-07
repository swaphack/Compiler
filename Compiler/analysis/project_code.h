#pragma once

#include "data/string_data.h"
#include "collections/map.h"
#include "collections/vector.h"
#include "project/project_path.h"

#ifdef __cplusplus
extern "C" {
#endif

struct struct_block;
struct function_block;

// ��������
typedef enum code_type
{
	ect_c,
}code_type;

// �ļ���
typedef struct code_file_block
{
	// �ṹ�� {string*, struct_block*}
	map* structs;
	// ���� {string*, function_block*}
	map* functions;

}code_file_block;

// �����ļ���Ϣ
typedef struct code_file
{
	// ·��
	string* filepath;
	// ����
	string* text;
	// �����ļ� {string*}
	vector* include_files;
	// �ļ��ṹ
	code_file_block* file_block;
	// ���� {string*}
	list* tokens;
}code_file;

struct analysis_table;
struct lexical_analysis;
// �����������
typedef struct code_analysis_method
{
	// ������
	struct analysis_table* table;
	// �ʷ�����
	struct lexical_analysis* scanning;

}code_analysis_method;

// ���̴���
typedef struct project_code
{
	// �����ļ� {string*, code_file*}
	map* code_files;
	// ����ļ�
	string* entry_file;
	// ����·��
	project_path* proj_path;
	// ������ȡ
	code_analysis_method* analysis_method;

	// �ṹ�� {string*, string*}
	map* structs;
	// ���� {string*, string*}
	map* functions;
	// ��ʱ����
	void* data;
}project_code;


code_file_block* init_code_file_block();
void free_code_file_block(code_file_block* cfb_ptr);

code_file* init_code_file();
void free_code_file(code_file* cf_ptr);

code_analysis_method* init_code_analysis_method();
void free_code_analysis_method(code_analysis_method* cam_ptr);

project_code* init_project_code();
void free_project_code(project_code* pc_ptr);

// �����ļ�
bool project_code_load_entry_file(project_code* pc_ptr, const char* filename);
bool project_code_load_file(project_code* pc_ptr, const char* filename);

// ���ҽṹ��
struct struct_block* project_code_get_struct_block(project_code* pc_ptr, const char* sb_name);
// ���Һ���
struct function_block* project_code_get_function_block(project_code* pc_ptr, const char* fb_name);

//  �������Գ�ʼ����������
void project_code_init_code_analysis_with(project_code* pc_ptr, code_type ct);


// map key=string* 
void del_map_string_code_file(void* key, void* value);


#ifdef __cplusplus
}
#endif