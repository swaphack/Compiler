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

// ��Ԫ��Ϣ
typedef struct analysis_token_unit
{
	// �ļ�·��
	string* filepath;
	// ����
	int line;
	// ����ȼ�
	analysis_level err_lv;
	// ��������
	string* err_text;
}analysis_token_unit;

// �����еĴ���
typedef struct analysis_error
{
	// �ʷ��׶δ��� {analysis_token_unit*}
	list* lexical_err;
	// �﷨�׶δ���{analysis_token_unit*}
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