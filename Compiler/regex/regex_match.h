#pragma once

#include "collections/list.h"
#include "data/string_data.h"
#include "stream/string_stream.h"

// 正则匹配表达式
#ifdef __cplusplus
extern "C" {
#endif

struct regex_meta;
// 匹配表达式
typedef struct regex_match
{
	size_t begin;
	size_t end;
	// 对应元符号
	struct regex_meta* meta_ptr;
}regex_match;

regex_match* init_regex_match();
void free_regex_match(regex_match* rm_ptr);


#ifdef __cplusplus
}

#endif