#pragma once

#include "map.h"
#include "list.h"
#include "vector.h"

#ifdef __cplusplus
extern "C" {
#endif


// string*, string*
int compare_string_key(void* a, void* b);
void del_string_key(void* a);
void del_map_string_key(void* a, void* b);

map* init_map_with_string_key(void (*del)(void* key, void* value));
// �ַ����ֵ�
map* init_string_map();
// �ַ�������
list* init_string_list();
// �ַ�������
vector* init_string_vector();


#ifdef __cplusplus
}
#endif