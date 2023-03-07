#pragma once

#include "macros.h"

// ����

#ifdef __cplusplus
extern "C" {
#endif

struct tree_node;
struct vector;

// �������������
void sort_vector(struct vector* vector_ptr, alg_compare_priority* func);

// ������������
void sort_tree(struct tree_node* tree_ptr, alg_compare_priority* func);


#ifdef __cplusplus
}

#endif