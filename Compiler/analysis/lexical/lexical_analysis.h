#pragma once

#include "data/macros.h"
#include "data/string_data.h"
// 词法分析 lexical analysis

#ifdef __cplusplus
extern "C" {
#endif

struct analysis_table;
// 词法分析 lexical analysis
typedef struct lexical_analysis
{
	// 文件路径
	string* filepath;
	// 读取到的行数
	int read_line;
	// 表 引用
	struct analysis_table* table_ptr;
}lexical_analysis;


lexical_analysis* init_lexical_analysis();
void free_lexical_analysis(lexical_analysis* la_ptr);


struct code_file;
// 过滤无效文本
void lexical_analysis_filter_invalid_words(lexical_analysis* la_ptr, struct code_file* cf_ptr);
// 加载词法单元
void lexical_analysis_load_tokens(lexical_analysis* la_ptr, struct code_file* cf_ptr);

// 扫描代码文件
void lexical_analysis_scan_code_file(lexical_analysis* la_ptr, struct code_file* cf_ptr);



#ifdef __cplusplus
}
#endif