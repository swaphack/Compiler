#pragma once

#include "macros.h"

// 转换
#ifdef __cplusplus
extern "C" {
#endif

struct vector;
struct tree;
struct tree_node;


// 对数组进行排序，将其变成树结构
struct tree_node* convert_tree_children_with_priority(struct tree_node* node, alg_get_priority* func);


#ifdef __cplusplus
}

#endif