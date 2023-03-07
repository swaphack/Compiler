#pragma once

#include "macros.h"

// ת��
#ifdef __cplusplus
extern "C" {
#endif

struct vector;
struct tree;
struct tree_node;


// ������������򣬽��������ṹ
struct tree_node* convert_tree_children_with_priority(struct tree_node* node, alg_get_priority* func);


#ifdef __cplusplus
}

#endif