#include "string_data.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "collections/hash.h"

CONSTRUCT_STRUCT(string);

#define CHAT_SIZE sizeof(char)

char* str_malloc(int capacity)
{
	if (capacity <= 0) return NULL;
	char* value = (char*)malloc(CHAT_SIZE * capacity);
	if (value == NULL) return NULL;
	memset(value, 0, CHAT_SIZE * capacity);

	return value;
}

char* str_realloc(char* value, int old_capacity, int new_capacity)
{
	if (new_capacity == 0 || new_capacity < old_capacity) return value;

	if (old_capacity == 0)
	{
		value = str_malloc(new_capacity);
	}
	else
	{
		char* temp = (char*)realloc(value, CHAT_SIZE * new_capacity);
		if (temp == NULL) return NULL;
		memset(temp + old_capacity, 0, CHAT_SIZE * (new_capacity - old_capacity));
		value = temp;
	}

	return value;
}

void free_string_value(string* data)
{
	if (data == NULL) return;
	if (data->value != NULL)
	{
		free(data->value);
		data->value = NULL;
	}
	data->size = 0;
	data->capacity = 0;
}

string* init_c_string(const char* value)
{
	if (value == NULL)
		return init_string("", 0);
	return init_string(value, strlen(value));
}

string* init_empty_string()
{
	string* data = init_string("", 0);
	return data;
}

string* init_string(const char* value, int size)
{
	if (value == NULL || size < 0)
	{
		return init_string("", 0);
	}

	int capacity = size + 1;

	char* temp = str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, value, CHAT_SIZE * size);

	string* data = create_string();
	if (data == NULL)
	{
		free(temp);
		return NULL;
	}
	string_init_with(data, temp, size, capacity);
	return data;
}

string* init_string_with_free(char* value, int size)
{
	if (value == NULL || size < 0) return NULL;

	string* str = init_string(value, size);
	free(value);
	return str;
}

#define BUFF_SIZE 512
static char buff[BUFF_SIZE] = { 0 };

string* format_string(char* format, ...)
{
	memset(buff, 0, BUFF_SIZE);

	int ret;
	va_list arg_list;
	va_start(arg_list, format);
	ret = vsprintf_s(buff, BUFF_SIZE, format, arg_list);
	va_end(arg_list);
	return init_string(buff, ret);
}

string* clone_string(string* data)
{
	if (data == NULL) return NULL;

	return init_string(data->value, data->size);
}

void string_init_with(string* data, const char* value, int size, int capacity)
{
	if (data == NULL)  return;
	data->value = (char*)value;
	data->size = size;
	data->capacity = capacity;
}

void string_clear(string* data)
{
	if (data->value == NULL || data->capacity == 0) return;
	
	char* temp = str_malloc(1);
	if (temp == NULL) return;
	free_string_value(data);
	string_init_with(data, temp, 0, 1);
}

void string_remove_at(string* data, int index)
{
	if (data == NULL || index < 0 || index >= data->size) return;
	if (data->value == NULL || data->size == 0) return;

	int capacity = data->capacity - 1;
	char* newValue = str_malloc(capacity);
	if (newValue == NULL) return;
	if (index > 0)
	{
		// 复制index前面的值
		memcpy(newValue, data->value, CHAT_SIZE * index);
	}	
	int after = index + 1;
	// 复制index之后的值
	memcpy(newValue + index, data->value + after, CHAT_SIZE * (data->size - after));
	free_string_value(data);
	string_init_with(data, newValue, data->size - 1, capacity);
}

void string_append_char(string* data, int count, char value)
{
	if (data == NULL || count <= 0) return;

	int capacity = data->capacity + count;
	char* temp = str_realloc(data->value, data->capacity, capacity);
	if (temp == NULL) return;

	memset(temp + data->size, value, CHAT_SIZE * count);
	string_init_with(data, temp, data->size + count, capacity);
}
void string_append_c_str(string* data, const char* value, int size)
{
	if (data == NULL || value == NULL || size <= 0) return;

	int capacity = data->capacity + size;
	char* temp = str_realloc(data->value, data->capacity, capacity);
	if (temp == NULL) return;

	memcpy(temp + data->size, value, size);

	string_init_with(data, temp, data->size + size, capacity);
}

void string_append_string(string* data, string* str)
{
	if (data == NULL || str == NULL) return;
	string_append_c_str(data, str->value, str->size);
}

void string_trim_start(string* data)
{
	if (data == NULL || data->size == 0 || data->value == NULL) return;
	int count = 0;
	for (int i = 0; i < data->size; i++)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		count++;
	}

	if (count == 0) return;

	int size = data->size - count;
	int capacity = data->capacity - count;
	char* temp = (char*)str_malloc(capacity);
	if (temp == NULL) return;
	memcpy(temp, data->value + count, CHAT_SIZE * size);
	free_string_value(data);
	string_init_with(data, temp, size, capacity);
}
void string_trim_end(string* data)
{
	if (data == NULL || data->size == 0 || data->value == NULL) return;
	int count = 0;
	for (int i = data->size - 1; i >= 0 ; i--)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		count++;
	}

	if (count == 0) return;

	int size = data->size - count;
	int capacity = data->capacity - count;

	char* temp = str_malloc(capacity);
	if (temp == NULL) return;
	memcpy(temp, data->value, CHAT_SIZE * size);
	free_string_value(data);
	string_init_with(data, temp, size, capacity);
}
void string_trim(string* data)
{
	if (data == NULL || data->size == 0 || data->value == NULL) return;
	int front_count = 0;
	int rear_count = 0;
	for (int i = 0; i < data->size; i++)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		front_count++;
	}
	for (int i = data->size - 1; i >= 0; i--)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		rear_count++;
	}

	if (front_count == 0 && rear_count == 0) return;
	if (front_count == data->size)
	{
		string_clear(data);
		return;
	}

	int size = data->size - front_count - rear_count;
	int capacity = data->capacity - front_count - rear_count;
	char* temp = str_malloc(capacity);
	if (temp == NULL) return;
	memcpy(temp, data->value + front_count, CHAT_SIZE * size);
	free_string_value(data);
	string_init_with(data, temp, size, capacity);
}

string* append_char(string* data, int count, char value)
{
	if (data == NULL || count == 0) return NULL;
	int capacity = data->capacity + count;
	char* temp = str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, data->value, data->size);
	memset(temp + data->size, value, count);
	int tsize = data->size + count;
	return init_string_with_free(temp, tsize);
}

string* append_c_str(string* data, const char* value, int size)
{
	if (data == NULL || value == NULL || size == 0) return NULL;

	int len = data->size + size;
	int capacity = data->capacity + size;
	char* temp = str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, data->value, data->size);
	memcpy(temp + data->size, value, size);
	int tsize = data->size + size;
	return init_string_with_free(temp, tsize);
}

string* append_string(string* data, string* str)
{
	if (data == NULL || str == NULL) return NULL;

	return append_c_str(data, str->value, str->size);
}
string* sub_string(string* data, int offset, int count)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;
	if (offset < 0 || offset >= data->size) return NULL;
	if (count < 0 || offset + count > data->size) return NULL;
	return init_string(data->value + offset, count);
}

void string_insert_c_str(string* data, int offset, const char* value, int size)
{
	if (data == NULL || data->value == NULL || data->size == 0) return;
	if (offset < 0 || offset > data->size) return;
	if (value == NULL || size <= 0) return;

	int capacity = data->capacity + size;
	char* temp = str_realloc(data->value, data->capacity, capacity);
	if (temp == NULL) return;

	memmove(temp + offset + size, temp + offset, data->size- offset);
	memcpy(temp + offset, value, size);

	string_init_with(data, temp, data->size + size, capacity);
}

void string_insert_string(string* data, int offset, string* str)
{
	if (data == NULL || str == NULL) return;

	string_insert_c_str(data, offset, str->value, str->size);
}

string* start_trim_string(string* data)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;

	int count = 0;
	for (int i = 0; i < data->size; i++)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		count++;
	}

	if (count == 0) return clone_string(data);

	int size = data->size - count;
	int capacity = data->capacity - count;
	char* temp = (char*)str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, data->value + count, CHAT_SIZE * size);
	return init_string_with_free(temp, size);
}

string* end_trim_string(string* data)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;

	int count = 0;
	for (int i = data->size - 1; i >= 0; i--)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		count++;
	}

	if (count == 0) return clone_string(data);

	int size = data->size - count;
	int capacity = data->capacity - count;

	char* temp = str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, data->value, CHAT_SIZE * size);
	return init_string_with_free(temp, size);
}

string* trim_string(string* data)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;

	int front_count = 0;
	int rear_count = 0;
	for (int i = 0; i < data->size; i++)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		front_count++;
	}
	for (int i = data->size - 1; i >= 0; i--)
	{
		if (data->value[i] != EMPTY_CHAR)
		{
			break;
		}
		rear_count++;
	}

	if (front_count == 0 && rear_count == 0) 
		return clone_string(data);

	if (front_count == data->size)
	{
		return init_empty_string();
	}

	int size = data->size - front_count - rear_count;
	int capacity = data->capacity - front_count - rear_count;
	char* temp = str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, data->value + front_count, CHAT_SIZE * size);
	return init_string_with_free(temp, size);
}

string* insert_c_str(string* data, int offset, const char* value, int size)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;
	if (offset < 0 || offset > data->size) return NULL;
	if (value == NULL || size <= 0) return NULL;

	int capacity = data->capacity + size;
	char* temp = str_malloc(capacity);
	if (temp == NULL) return NULL;
	memcpy(temp, data->value, offset);
	memcpy(temp + offset, value, size);
	memcpy(temp + offset + size, data->value + offset, data->size - offset);
	int tsize = data->size + size;
	return init_string_with_free(temp, tsize);
}

string* insert_string(string* data, int offset, string* str)
{
	if (data == NULL || str == NULL) return NULL;

	return insert_c_str(data, offset, str->value, str->size);
}

bool string_starts_with(string* data, const char* value, int size)
{
	if (data == NULL || data->value == NULL || data->size == 0) return false;
	if (value == NULL || size <= 0) return false;
	if (data->size < size) return false;
	int ret = memcmp(data->value, value, size);
	return ret == 0;
}
bool string_ends_with(string* data, const char* value, int size)
{
	if (data == NULL || data->value == NULL || data->size == 0) return false;
	if (value == NULL || size <= 0) return false;
	if (data->size < size) return false;
	int ret = memcmp(data->value + data->size - size, value, CHAT_SIZE * size);
	return ret == 0;
}

char string_char_at(string* data, int index)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NUL_CHAR;
	if (index < 0 || index >= data->size) return NUL_CHAR;
	return data->value[index];
}


int string_first_index(string* data, const char* value, int size)
{
	return string_first_index_with_offset(data, 0, value, size);
}

int string_first_index_with_offset(string* data, int offset, const char* value, int size)
{
	if (data == NULL || data->value == NULL || data->size == 0) return -1;
	if (value == NULL || size <= 0) return -1;
	if (data->size < size) return -1;
	if (offset < 0 || offset >= data->size) return -1;

	int index = 0;
	while (offset < data->size)
	{
		if (data->value[offset] == value[index])
		{
			index++;
		}
		else
		{
			index = 0;
		}

		if (index == 0 && data->value[offset] == value[index])
		{
			index++;
		}

		if (index > 0 && index == size)
		{
			return offset + 1 - size;
		}

		offset++;
	}
	return -1;
}

int string_last_index(string* data, const char* value, int size)
{
	return string_last_index_with_offset(data, data->size - 1, value, size);
}

int string_last_index_with_offset(string* data, int offset, const char* value, int size)
{
	if (data == NULL || data->value == NULL || data->size == 0) return -1;
	if (value == NULL || size <= 0) return -1;
	if (data->size < size) return -1;
	if (offset < 0 || offset >= data->size) return -1;

	int index = size;
	while (offset >= 0)
	{
		if (data->value[offset] == value[index - 1])
		{
			index--;
		}
		else
		{
			index = size;
		}

		if (index == size && data->value[offset] == value[index])
		{
			index--;
		}

		if (index == 0)
		{
			return offset;
		}

		offset--;
	}
	return -1;
}

string* string_replace(string* data, const char* srcValue, int srcSize, const char* destValue, int destSize)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;
	if (srcValue == NULL || srcSize <= 0) return NULL;
	if (destValue == NULL || destSize <= 0) return NULL;
	if (data->size < srcSize) return NULL;

	int* ary = NULL;
	int len = 0;
	int cursor = 0;
	while (true)
	{
		int offset = string_first_index_with_offset(data, cursor, srcValue, srcSize);
		if (offset == -1) break;

		len++;
		if (ary == NULL)
		{
			int* temp = (int*)malloc(len * sizeof(int));
			if (temp == NULL) break;
			ary = temp;
		}
		else
		{
			int* temp = (int*)realloc(ary, len * sizeof(int));
			if (temp == NULL) break;
			ary = temp;
		}
		ary[len - 1] = offset;

		cursor = offset + srcSize;
	}

	if (len == 0 || ary == NULL)
	{
		return clone_string(data);
	}

	int capacity = data->capacity + len * (destSize - srcSize);
	int last = 0;
	int temp_cursor = 0;
	char* temp_value = str_malloc(capacity);
	if (temp_value == NULL) return NULL;
	for (int i = 0; i < len; i++)
	{
		int offset = ary[i];
		int diff = offset - last;
		if (diff != 0)
		{
			memcpy(temp_value + temp_cursor, data->value + last, diff * CHAT_SIZE);
			temp_cursor += diff;
		}
		memcpy(temp_value + temp_cursor, destValue, destSize * CHAT_SIZE);
		temp_cursor += destSize;
		last = offset + srcSize;	
	}
	int remain = data->size - ary[len - 1] - srcSize;
	if (remain > 0)
	{
		memcpy(temp_value + temp_cursor, data->value + ary[len - 1] + srcSize, remain * CHAT_SIZE);
	}
	int size = data->size + len * (destSize - srcSize);
	return init_string_with_free(temp_value, size);
}
string** string_split(string* data, const char* splitValue, int splitSize, int* splitCount)
{
	if (data == NULL || data->value == NULL || data->size == 0) return NULL;
	if (splitValue == NULL || splitSize <= 0 || splitCount == NULL) return NULL;
	if (data->size < splitSize) return NULL;

	*splitCount = 0;

	string** split_ptr = (string**)malloc(sizeof(string*));
	if (split_ptr == NULL) return NULL;

	int cursor = 0;
	int start_cursor = 0;
	int end_cursor = 0;
	int offset = 0;

	int split_count = 0;
	bool has_error = false;
	while (cursor < data->size)
	{
		if (data->value[cursor] == splitValue[offset])
		{
			offset++;
			if (offset == splitSize)
			{
				end_cursor = cursor - splitSize;
				int cur_size = end_cursor - start_cursor;
				if (cur_size > 0)
				{
					void* temp_str = init_string(data->value + start_cursor, cur_size);
					if (temp_str == NULL)
					{
						has_error = true;
						break;
					}
					split_ptr[split_count] = (string*)temp_str;
					split_count += 1;
					void* temp_ptr = realloc(split_ptr, split_count * sizeof(string*));
					if (temp_ptr == NULL)
					{
						has_error = true;
						break;
					}
					split_ptr = (string**)temp_ptr;
				}

				end_cursor = 0;
				start_cursor = cursor;
			}
		}
		else
		{
			offset = 0;
		}

		cursor++;
	}

	if (has_error == true)
	{
		free(split_ptr);
		split_ptr = NULL;
		return NULL;
	}

	do
	{
		int cur_size = data->size - start_cursor;
		if (cur_size > 0)
		{
			void* temp_str = init_string(data->value + start_cursor, cur_size);
			if (temp_str == NULL)
			{
				has_error = true;
				break;
			}

			split_ptr[split_count] = (string*)temp_str;
			split_count += 1;
			void* temp_ptr = realloc(split_ptr, split_count * sizeof(string*));
			if (temp_ptr == NULL)
			{
				has_error = true;
				break;
			}
			split_ptr = (string**)temp_ptr;
		}
	} while (0);

	if (has_error == true)
	{
		free(split_ptr);
		split_ptr = NULL;
		return NULL;
	}

	*splitCount = split_count;
	return split_ptr;
}

void free_string(string* data)
{
	if (data == NULL) return;
	string_clear(data);
	destroy_string(data);
}

string* string_concate(string** strings, int count, string* spilt)
{
	if (strings == NULL || count == 0) return NULL;

	int ssize = 0;
	if (spilt != NULL)
	{
		ssize = spilt->size;
	}
	int size = ssize * (count -1);
	for (int i = 0; i < count; i++)
	{
		if (strings[i] != NULL)
		{
			size += strings[i]->size;
		}
	}
	
	int offset = 0;
	char* temp = str_malloc(size + 1);
	if (temp == NULL) return NULL;
	for (int i = 0; i < count; i++)
	{
		string* str = strings[i];
		if (str != NULL)
		{
			memcpy(temp + offset, str->value, str->size);
			offset += str->size;
			if ((ssize > 0) && (i < count - 1))
			{
				memcpy(temp + offset, spilt->value, ssize);
				offset += ssize;
			}
		}
	}

	return init_string_with_free(temp, size);
}

void free_string_array(string** strings, int count)
{
	if (strings == NULL || count == 0) return;

	for (int i = 0; i < count; i++)
	{
		free_string(strings[i]);
	}

	free(strings);
	strings = NULL;
}

bool string_is_null_or_empty(const string* data)
{
	if (data == NULL) return true;
	if (data->size == 0 || data->value == NULL) return true;
	return false;
}

int compare_char(char a, char b)
{
	if (a > b) return 1;
	if (a < b) return -1;
	return 0;
}

int compare_string(const string* a, const string* b)
{
	if (a == NULL && b == NULL) return 0;
	if (a == NULL) return -1;
	if (b == NULL) return 1;

	return strcmp(a->value, b->value);
}
int compare_string_with_c_str(const string* a, const char* b)
{
	if (a == NULL && b == NULL) return 0;
	if (a == NULL) return -1;
	if (b == NULL) return 1;

	return strcmp(a->value, b);
}


//////////////////////////////////////////////////////
CONSTRUCT_STRUCT(hash_string)

hash_string* init_hash_c_string(const char* value)
{
	if (value == NULL) return NULL;

	return init_hash_string(value, strlen(value));
}

hash_string* init_hash_string(const char* value, int size)
{
	if (value == NULL || size == 0) return NULL;

	hash_string* hs_ptr = create_hash_string();
	if (hs_ptr == NULL) return NULL;
	hs_ptr->value = init_string(value, size);
	if (hs_ptr->value != NULL)
	{
		hs_ptr->hash = get_hash_code(value);
	}
	return hs_ptr;
}
void free_hash_string(hash_string* data)
{
	if (data == NULL) return;
	if (data->value != NULL)
	{
		free_string(data->value);
		data->value = NULL;
	}

	destroy_hash_string(data);
	data = NULL;
}
int compare_hash_string(const hash_string* a, const hash_string* b)
{
	if (a == NULL && b == NULL) return 0;
	if (a == NULL) return -1;
	if (b == NULL) return 1;
	if (a->hash < b->hash) return -1;
	if (a->hash > b->hash) return 1;
	return compare_string(a->value, b->value);
}