#pragma once

#include "data/macros.h"
#include "data/string_data.h"
// �ʷ����� lexical analysis

#ifdef __cplusplus
extern "C" {
#endif

struct analysis_table;
// �ʷ����� lexical analysis
typedef struct lexical_analysis
{
	// �ļ�·��
	string* filepath;
	// ��ȡ��������
	int read_line;
	// �� ����
	struct analysis_table* table_ptr;
}lexical_analysis;


lexical_analysis* init_lexical_analysis();
void free_lexical_analysis(lexical_analysis* la_ptr);


struct code_file;
// ������Ч�ı�
void lexical_analysis_filter_invalid_words(lexical_analysis* la_ptr, struct code_file* cf_ptr);
// ���شʷ���Ԫ
void lexical_analysis_load_tokens(lexical_analysis* la_ptr, struct code_file* cf_ptr);

// ɨ������ļ�
void lexical_analysis_scan_code_file(lexical_analysis* la_ptr, struct code_file* cf_ptr);



#ifdef __cplusplus
}
#endif