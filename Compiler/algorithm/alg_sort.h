#pragma once

#include "macros.h"

// 排序

#ifdef __cplusplus
extern "C" {
#endif

struct tree_node;
struct vector;

// 对数组进行排序
void sort_vector(struct vector* vector_ptr, alg_compare_priority* func);

// 对树重新排序
void sort_tree(struct tree_node* tree_ptr, alg_compare_priority* func);


#ifdef __cplusplus
}

#endif