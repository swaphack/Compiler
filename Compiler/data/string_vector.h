#pragma once


#include "collections/vector.h"
#include "data/string_data.h"
#include "stream/string_stream.h"


#ifdef __cplusplus
extern "C" {
#endif

// �ַ���������
typedef struct vector_string
{
	// �ַ������� {string*}
	vector* strings;
	//  ��ǰ
	int index;
	// �Ƿ����
	bool over;
	// ��ǰ�ַ�����
	string_stream* stream;
}vector_string;

vector_string* init_vector_string();
void vector_string_init_with(vector_string* vs_ptr, string** strings, int count);
void free_vector_string(vector_string* vs_ptr);

string* vector_string_get_cur_string(vector_string* vs_ptr);
string_stream* vector_string_get_string_stream(vector_string* vs_ptr);
char vector_string_read_next_char(vector_string* vs_ptr);
string* vector_string_read_string(vector_string* vs_ptr, int size);
string* vector_string_read_next_string(vector_string* vs_ptr);

void vector_string_free_string_stream(vector_string* vs_ptr);
void vector_string_set_index(vector_string* vs_ptr, int index);
bool vector_string_move_next(vector_string* vs_ptr);

string* combine_vector_string(vector_string* vs_ptr, string* spilt);


#ifdef __cplusplus
}
#endif