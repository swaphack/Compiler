#pragma once

#include "macros.h"
#include "collections/list.h"
#include "string_data.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct string_builder
{
	// {string*}
	list* list;
}string_builder;

string_builder* init_string_builder();
void string_builder_append_char(string_builder* sb_ptr, int cout, char c);
void string_builder_append(string_builder* sb_ptr, string* str);
void string_builder_append_format(string_builder* sb_ptr, char* format, ...);
void string_builder_appendln(string_builder* sb_ptr);
string* string_builder_to_string(string_builder* sb_ptr);
void free_string_builder(string_builder* sb_ptr);


#ifdef __cplusplus
}
#endif