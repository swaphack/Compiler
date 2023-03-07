#pragma once
#include "data/macros.h"

#ifdef __cplusplus
extern "C" {
#endif

// 容器初始大小
#define COLLECTION_CAPACITY 4
// 指针大小
#define VOID_PTR_SIZE sizeof(void*)

// 比较容器数据
typedef int cmp_collection_data(void* a, void* b);
// 删除容器数据
typedef void del_collection_data(void* a);
// 删除map容器数据
typedef void del_map_data(void* key, void* value);
// 查找数据
typedef bool find_collection_data(void* a, void* b);
// 遍历数据
typedef void foreach_collection_data(void* a, void* b);
// 遍历节点
typedef void foreach_collection_node(void* a, void* b);
#ifdef __cplusplus
}
#endif


