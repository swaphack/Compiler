#pragma once

#include "collections/list.h"
#include "data/string_data.h"
#include "stream/string_stream.h"

#ifdef __cplusplus
extern "C" {
#endif

// �ַ���������
typedef struct list_string
{
	// �ַ������� {string*}
	list* strings;
	//  ��ǰ
	list_node* node;
	// �Ƿ����
	bool over;
	// ��ǰ�ַ�����
	string_stream* stream;
}list_string;


list_string* init_list_string();
void list_string_init_with(list_string* ls_ptr, list* strings);
void free_list_string(list_string* ls_ptr);

list_node* list_string_get_cur_node(list_string* ls_ptr);
string_stream* list_string_get_string_stream(list_string* ls_ptr);
char list_string_read_next_char(list_string* ls_ptr);
string* list_string_read_string(list_string* ls_ptr, int size);
string* list_string_read_next_string(list_string* ls_ptr);

void list_string_free_string_stream(list_string* ls_ptr);
void list_string_set_node(list_string* ls_ptr, list_node* node);
bool list_string_move_next(list_string* ls_ptr);

string* combine_list_string(list_string* ls_ptr, string* spilt);


#ifdef __cplusplus
}
#endif