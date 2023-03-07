#include "string_stream.h"

#include "data/macros.h"

CONSTRUCT_STRUCT(string_stream);

string_stream* init_string_stream()
{
	string_stream* ss_ptr = create_string_stream();
	ss_ptr->string = init_empty_string();
	return ss_ptr;
}

void string_stream_init_with(string_stream* ss_ptr, string* string, int cursor)
{
	if (ss_ptr == NULL) return;
	free_string(ss_ptr->string);

	ss_ptr->string = clone_string(string);
	ss_ptr->cursor = cursor;
	ss_ptr->freestr = true;
}

void string_stream_init_with_ptr(string_stream* ss_ptr, string* string, int cursor)
{
	if (ss_ptr == NULL) return;
	free_string(ss_ptr->string);
	ss_ptr->string = string;
	ss_ptr->cursor = cursor;
	ss_ptr->freestr = false;
}

void free_string_stream(string_stream* ss_ptr)
{
	if (ss_ptr == NULL) return;
	if (ss_ptr->freestr && ss_ptr->string != NULL)
	{
		free_string(ss_ptr->string);
		ss_ptr->string = NULL;
	}
	
	destroy_string_stream(ss_ptr);
	ss_ptr = NULL;
}

string* sub_string_stream(string_stream* ss_ptr, int offset, int count)
{
	if (ss_ptr == NULL || ss_ptr->string == NULL) return NULL;
	if (offset < 0 || offset >= ss_ptr->string->size) return NULL;
	if (offset + count > ss_ptr->string->size) return NULL;

	return init_string(ss_ptr->string->value + offset, count);
}

void string_stream_seek(string_stream* ss_ptr, int offset, seek_stream ss)
{
	if (ss_ptr == NULL) return;
	if (string_is_null_or_empty(ss_ptr->string)) return;

	int cursor = 0;
	if (ss == ess_start)
	{
		cursor = offset;			
	}
	else if (ss == ess_cur)
	{
		cursor = offset + ss_ptr->cursor;
	}
	else
	{
		cursor = ss_ptr->string->size - offset;
	}

	if (cursor < 0) cursor = 0;
	if (cursor >= ss_ptr->string->size) cursor = ss_ptr->string->size - 1;

	ss_ptr->cursor = cursor;
}
void string_stream_append(string_stream* ss_ptr, string* str)
{
	if (ss_ptr == NULL || str == NULL) return;
	if (string_is_null_or_empty(str)) return;

	string_append_string(ss_ptr->string, str);
}
void string_stream_insert(string_stream* ss_ptr, int offset, string* str)
{
	if (ss_ptr == NULL || str == NULL) return;
	if (string_is_null_or_empty(str)) return;
	if (offset == 0 || offset >= ss_ptr->string->size) return;

	string_insert_string(ss_ptr->string, offset, str);

}
string* string_stream_read(string_stream* ss_ptr, int size)
{
	if (ss_ptr == NULL) return NULL;
	if (string_is_null_or_empty(ss_ptr->string)) return NULL;
	if (ss_ptr->cursor + size > ss_ptr->string->size) return NULL;

	string* str = sub_string(ss_ptr->string, ss_ptr->cursor, size);
	if (str == NULL) return NULL;
	ss_ptr->cursor += size;
	return str;
}

char string_stream_read_char(string_stream* ss_ptr)
{
	if (ss_ptr == NULL) return NUL_CHAR;
	if (string_is_null_or_empty(ss_ptr->string)) return NUL_CHAR;
	if (ss_ptr->cursor + 1 > ss_ptr->string->size) return NUL_CHAR;

	char str = string_stream_char_at_cursor(ss_ptr);
	ss_ptr->cursor += 1;
	return str;
}

int string_stream_first_index(string_stream* ss_ptr, const char* str)
{
	if (ss_ptr == NULL || str == NULL) return -1;
	int len = strlen(str);
	if (len == 0) return -1;

	if (ss_ptr->cursor + len > ss_ptr->string->size) return -1;

	return string_last_index_with_offset(ss_ptr->string, ss_ptr->cursor, str, len);
}

bool string_stream_is_over(string_stream* ss_ptr)
{
	if (ss_ptr == NULL) return true;
	if (string_is_null_or_empty(ss_ptr->string)) return true;
	if (ss_ptr->cursor >= ss_ptr->string->size) return true;

	return false;
}

char string_stream_char_at(string_stream* ss_ptr, int index)
{
	if (ss_ptr == NULL) return NUL_CHAR;
	if (ss_ptr->string == NULL) return NUL_CHAR;

	return string_char_at(ss_ptr->string, index);
}

char string_stream_char_at_cursor(string_stream* ss_ptr)
{
	return string_stream_char_at(ss_ptr, ss_ptr->cursor);
}

bool string_stream_move_next(string_stream* ss_ptr)
{
	if (ss_ptr == NULL) return false;

	return string_stream_move(ss_ptr, 1);
}

bool string_stream_move(string_stream* ss_ptr, int offset)
{
	if (ss_ptr == NULL) return false;
	if (ss_ptr->string == NULL) return false;
	if (ss_ptr->cursor >= ss_ptr->string->size) return false;

	int cursor = ss_ptr->cursor + offset;
	if (cursor < 0) cursor = 0;
	if (cursor > ss_ptr->string->size) cursor = ss_ptr->string->size;

	ss_ptr->cursor = cursor;

	return true;
}

bool string_stream_can_read(string_stream* ss_ptr, int count)
{
	if (ss_ptr == NULL) return false;
	if (ss_ptr->string == NULL) return false;

	return ss_ptr->cursor + count <= ss_ptr->string->size;
}

bool string_stream_equal_string(string_stream* ss_ptr, string* str)
{
	if (ss_ptr == NULL || str == NULL) return false;
	if (ss_ptr->cursor + str->size > ss_ptr->string->size) return false;

	for (int i = 0; i < str->size; i++)
	{
		char c1 = string_stream_char_at(ss_ptr, i + ss_ptr->cursor);
		char c2 = str->value[i];
		int ret = compare_char(c1, c2);
		if (ret != 0) return false;
	}
	return true;
}

bool string_stream_equal_c_str(string_stream* ss_ptr, const char* str)
{
	if (ss_ptr == NULL || str == NULL) return false;
	int len = strlen(str);
	if (len == 0) return false;
	if (ss_ptr->cursor + len > ss_ptr->string->size) return false;

	for (int i = 0; i < len; i++)
	{
		char c1 = string_stream_char_at(ss_ptr, i + ss_ptr->cursor);
		char c2 = str[i];
		int ret = compare_char(c1, c2);
		if (ret != 0) return false;
	}
	return true;
}

