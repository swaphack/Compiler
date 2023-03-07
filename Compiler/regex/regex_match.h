#pragma once

#include "collections/list.h"
#include "data/string_data.h"
#include "stream/string_stream.h"

// ����ƥ����ʽ
#ifdef __cplusplus
extern "C" {
#endif

struct regex_meta;
// ƥ����ʽ
typedef struct regex_match
{
	size_t begin;
	size_t end;
	// ��ӦԪ����
	struct regex_meta* meta_ptr;
}regex_match;

regex_match* init_regex_match();
void free_regex_match(regex_match* rm_ptr);


#ifdef __cplusplus
}

#endif