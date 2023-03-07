#pragma once

#include "data/string_data.h"
#include "stream.h"

#ifdef __cplusplus
extern "C" {
#endif

// 字符串流
typedef struct string_stream
{
	string* string;
	int cursor;
	// 是否释放string
	bool freestr;
}string_stream;


string_stream* init_string_stream();
void string_stream_init_with(string_stream* ss_ptr, string* string, int cursor);
void string_stream_init_with_ptr(string_stream* ss_ptr, string* string, int cursor);
void free_string_stream(string_stream* ss_ptr);

string* sub_string_stream(string_stream* ss_ptr, int offset, int count);

void string_stream_seek(string_stream* ss_ptr, int offset, seek_stream ss);
void string_stream_append(string_stream* ss_ptr, string* str);
void string_stream_insert(string_stream* ss_ptr, int offset, string* str);

// 从游标开始
string* string_stream_read(string_stream* ss_ptr, int size);
char string_stream_read_char(string_stream* ss_ptr);
int string_stream_first_index(string_stream* ss_ptr, const char* str);
char string_stream_char_at_cursor(string_stream* ss_ptr);
bool string_stream_move_next(string_stream* ss_ptr);
bool string_stream_can_read(string_stream* ss_ptr, int count);
bool string_stream_equal_string(string_stream* ss_ptr, string* str);
bool string_stream_equal_c_str(string_stream* ss_ptr, const char* str);


char string_stream_char_at(string_stream* ss_ptr, int index);
bool string_stream_is_over(string_stream* ss_ptr);
bool string_stream_move(string_stream* ss_ptr, int offset);

#ifdef __cplusplus
}
#endif