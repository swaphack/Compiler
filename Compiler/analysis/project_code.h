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

// 代码类型
typedef enum code_type
{
	ect_c,
}code_type;

// 文件块
typedef struct code_file_block
{
	// 结构体 {string*, struct_block*}
	map* structs;
	// 函数 {string*, function_block*}
	map* functions;

}code_file_block;

// 代码文件信息
typedef struct code_file
{
	// 路径
	string* filepath;
	// 内容
	string* text;
	// 包含文件 {string*}
	vector* include_files;
	// 文件结构
	code_file_block* file_block;
	// 符号 {string*}
	list* tokens;
}code_file;

struct analysis_table;
struct lexical_analysis;
// 代码分析方法
typedef struct code_analysis_method
{
	// 分析表
	struct analysis_table* table;
	// 词法分析
	struct lexical_analysis* scanning;

}code_analysis_method;

// 工程代码
typedef struct project_code
{
	// 代码文件 {string*, code_file*}
	map* code_files;
	// 入口文件
	string* entry_file;
	// 工程路径
	project_path* proj_path;
	// 代码提取
	code_analysis_method* analysis_method;

	// 结构体 {string*, string*}
	map* structs;
	// 函数 {string*, string*}
	map* functions;
	// 临时数据
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

// 加载文件
bool project_code_load_entry_file(project_code* pc_ptr, const char* filename);
bool project_code_load_file(project_code* pc_ptr, const char* filename);

// 查找结构体
struct struct_block* project_code_get_struct_block(project_code* pc_ptr, const char* sb_name);
// 查找函数
struct function_block* project_code_get_function_block(project_code* pc_ptr, const char* fb_name);

//  根据语言初始化分析方法
void project_code_init_code_analysis_with(project_code* pc_ptr, code_type ct);


// map key=string* 
void del_map_string_code_file(void* key, void* value);


#ifdef __cplusplus
}
#endif