#pragma once

#include "data/macros.h"
#include "data/string_data.h"
#include "collections/list.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum analysis_level
{
	eal_warning,
	eal_error,
}analysis_level;

// 单元信息
typedef struct analysis_token_unit
{
	// 文件路径
	string* filepath;
	// 行数
	int line;
	// 错误等级
	analysis_level err_lv;
	// 错误内容
	string* err_text;
}analysis_token_unit;

// 分析中的错误
typedef struct analysis_error
{
	// 词法阶段错误 {analysis_token_unit*}
	list* lexical_err;
	// 语法阶段错误{analysis_token_unit*}
	list* syntax_err;
}analysis_error;

analysis_token_unit* init_analysis_token_unit();
void free_analysis_token_unit(analysis_token_unit* atu_ptr);

analysis_error* init_analysis_error();
void free_analysis_error(analysis_error* ae_ptr);

void analysis_error_add_lexical_unit(analysis_error* ae_ptr, analysis_token_unit* atu_ptr);
void analysis_error_add_syntax_unit(analysis_error* ae_ptr, analysis_token_unit* atu_ptr);

#ifdef __cplusplus
}
#endif