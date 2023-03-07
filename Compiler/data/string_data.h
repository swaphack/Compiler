#pragma once

#include "macros.h"
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

#define EMPTY_CHAR ' '
#define NUL_CHAR '\0'
#define LINE_BREAK_CHAR '\n'
#define TAB_CHAR '\t'
#define CARRIAGE_RETURN_CHAR '\r'

typedef struct string
{
	char* value;
	int size;
	int capacity;
} string;


char* str_malloc(int capacity);
char* str_realloc(char* value, int old_capacity, int new_capacity);

string* init_c_string(const char* value);
string* init_empty_string();
string* init_string(const char* value, int size);
string* init_string_with_free(char* value, int size);
string* format_string(char* format, ...);
string* clone_string(string* data);

void string_init_with(string* data, const char* value, int size, int capacity);
void string_clear(string* data);
void string_remove_at(string* data, int index);
void string_append_char(string* data, int count, char value);
void string_append_c_str(string* data, const char* value, int size);
void string_append_string(string* data, string* str);
void string_trim_start(string* data);
void string_trim_end(string* data);
void string_trim(string* data);
void string_insert_c_str(string* data, int offset, const char* value, int size);
void string_insert_string(string* data, int offset, string* str);

string* start_trim_string(string* data);
string* end_trim_string(string* data);
string* trim_string(string* data);
string* append_char(string* data, int count, char value);
string* append_c_str(string* data, const char* value, int size);
string* append_string(string* data, string* str);
string* sub_string(string* data, int offset, int count);
string* insert_c_str(string* data, int offset, const char* value, int size);
string* insert_string(string* data, int offset, string* str);

bool string_starts_with(string* data, const char* value, int size);
bool string_ends_with(string* data, const char* value, int size);
char string_char_at(string* data, int index);
int string_first_index(string* data, const char* value, int size);
int string_first_index_with_offset(string* data, int offset, const char* value, int size);
int string_last_index(string* data, const char* value, int size);
int string_last_index_with_offset(string* data, int offset, const char* value, int size);
string* string_replace(string* data, const char* srcValue, int srcSize, const char* destValue, int destSize);
string** string_split(string* data, const char* splitValue, int splitSize, int* splitCount);
void free_string(string* data);


string* string_concate(string** strings, int count, string* spilt);
void free_string_array(string** strings, int count);

bool string_is_null_or_empty(const string* data);
int compare_char(char a, char b);
int compare_string(const string* a, const string* b);
int compare_string_with_c_str(const string* a, const char* b);


//////////////////////////////////////////////////////
typedef struct hash_string
{
	// ��ϣֵ
	uint64_t hash;
	// ֵ
	string* value;
} hash_string;

hash_string* init_hash_c_string(const char* value);
hash_string* init_hash_string(const char* value, int size);
void free_hash_string(hash_string* data);
int compare_hash_string(const hash_string* a, const hash_string* b);


#ifdef __cplusplus
}
#endif