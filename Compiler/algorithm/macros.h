#pragma once


#ifdef __cplusplus
extern "C" {
#endif

// 优先级比较
typedef int alg_compare_priority(void* a, void* b);
// 获取优先级
typedef int alg_get_priority(void* a);

#ifdef __cplusplus
}

#endif