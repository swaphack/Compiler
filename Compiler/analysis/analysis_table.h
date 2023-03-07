#pragma once

#include "symbol_table.h"
#include "collections/map.h"
#include "collections/list.h"
#ifdef __cplusplus
extern "C" {
#endif

#define TABLE_PREPROCESS_ID "preprocess"
#define TABLE_KEY_NAME "key"
#define TABLE_SYMBOL_NAME "symbol"
#define TABLE_FUNCTION_NAME "function"
#define TABLE_STRUCT_NAME "struct"

// �ʷ���
typedef enum lexical_table_type
{
	// Ԥ�����
	eltt_preprocess,
	// ���ű�
	eltt_symbol,
	// �ؼ��ֱ�
	eltt_key,
	// ������
	eltt_function,
	// ���ͱ�
	eltt_struct,
	// ���
	eltt_block,
}lexical_table_type;

// �ʷ���Ԫ
typedef struct lexical_token
{
	// ���� ����
	hash_string* name;
	// sysmbol_table ����
	int sysmbol_index;
	// ���ֶ�����
	string* lt_name;
	// ������
	lexical_table_type table_type;
}lexical_token;

// �ʷ����� lexical analysis
typedef struct analysis_table
{
	// Ԥ�����
	symbol_table* preprocess_table;
	// ���ű�
	symbol_table* sign_table;
	// �ؼ��ֱ�
	symbol_table* key_table;
	// ���ͱ�
	symbol_table* struct_table;
	// ������
	symbol_table* function_table;
	// ��� [ ] {} ()
	map* block_table;
	// ���÷��ű� {string*}
	list* invalid_table;
}analysis_table;

analysis_table* init_analysis_table();
void free_analysis_table(analysis_table* at_ptr);

//�������� type : lexical_table_type
int lexical_analysis_token_index(analysis_table* at_ptr, string* str, int* type);
// �������� type : lexical_table_type
struct lexical_token* lexical_analysis_create_token(analysis_table* at_ptr, int type, int index, string* str);


#ifdef __cplusplus
}
#endif