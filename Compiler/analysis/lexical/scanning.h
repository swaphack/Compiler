#pragma once

#include "collections/list.h"
#include "collections/set.h"
#include "data/data.h"
#include "data/string_data.h"
#include "analysis/symbol_table.h"
#include "stream/string_stream.h"

// �ʷ����� lexical analysis

#ifdef __cplusplus
extern "C" {
#endif


// ����
typedef struct lexical_sentence
{
	// ���� {string*}
	vector* tokens;
	// �ı�
	string* text;
}lexical_sentence;

// ��
typedef struct lexical_block
{
	int index;
	// ����{lexical_sentence*}
	list* sentences;
	// ��{lexical_block*}
	list* blocks;
}lexical_block;


lexical_sentence* init_lexical_sentence();
void free_lexical_sentence(lexical_sentence* ls_ptr);

lexical_block* init_lexical_block();
void free_lexical_block(lexical_block* ll_ptr);

// �Ƿ�������
bool is_number_string(const string* data);
// �Ƿ�����ĸ
bool is_letter_string(const string* data);
// �Ƿ��Ǳ���
bool is_variable_string(const string* data);

#ifdef __cplusplus
}
#endif