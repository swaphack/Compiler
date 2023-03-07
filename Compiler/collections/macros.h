#pragma once
#include "data/macros.h"

#ifdef __cplusplus
extern "C" {
#endif

// ������ʼ��С
#define COLLECTION_CAPACITY 4
// ָ���С
#define VOID_PTR_SIZE sizeof(void*)

// �Ƚ���������
typedef int cmp_collection_data(void* a, void* b);
// ɾ����������
typedef void del_collection_data(void* a);
// ɾ��map��������
typedef void del_map_data(void* key, void* value);
// ��������
typedef bool find_collection_data(void* a, void* b);
// ��������
typedef void foreach_collection_data(void* a, void* b);
// �����ڵ�
typedef void foreach_collection_node(void* a, void* b);
#ifdef __cplusplus
}
#endif


