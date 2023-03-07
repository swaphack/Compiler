#include "string_builder.h"
#include "collections/extensions.h"
#include <stdarg.h>
#include <stdio.h>

CONSTRUCT_STRUCT(string_builder);

string_builder* init_string_builder()
{
	string_builder* sb = create_string_builder();
	if (sb == NULL) return NULL;
	sb->list = init_string_list();
	return sb;
}

void string_builder_append_char(string_builder* sb_ptr, int cout, char c)
{
	if (sb_ptr == NULL) return;
	string* str = init_empty_string();
	if (str == NULL) return;
	string_append_char(str, cout, c);
	string_builder_append(sb_ptr, str);
}

void string_builder_append(string_builder* sb_ptr, string* str)
{
	if (sb_ptr == NULL || str == NULL) return;

	list_append_data(sb_ptr->list, str);
}

#define BUFF_SIZE 512
static char buff[BUFF_SIZE] = { 0 };

void string_builder_append_format(string_builder* sb_ptr, char* format, ...)
{
	if (sb_ptr == NULL) return;

	memset(buff, 0, BUFF_SIZE);

	int ret;
	va_list arg_list;
	va_start(arg_list, format);
	ret = vsprintf_s(buff, BUFF_SIZE, format, arg_list);
	va_end(arg_list);
	string* str = init_string(buff, ret);
	if (str == NULL) return;

	string_builder_append(sb_ptr, str);
}

void string_builder_appendln(string_builder* sb_ptr)
{
	if (sb_ptr == NULL) return;

	string_builder_append(sb_ptr, init_c_string("\r\n"));
}
string* string_builder_to_string(string_builder* sb_ptr)
{
	if (sb_ptr == NULL) return NULL;
	if (sb_ptr->list == NULL || sb_ptr->list->root == NULL) return NULL;

	list_node* node = sb_ptr->list->root;

	int total_size = 0;
	int str_size = 0;
	char* data = NULL;

	bool has_error = false;
	while (node != NULL)
	{
		string* temp = (string*)node->data;
		str_size = temp->size;
		if (data == NULL)
		{
			char* temp = (char*)malloc(str_size);
			if (temp == NULL)
			{
				has_error = true;
				break;
			}
			data = temp;
		}
		else
		{
			char* temp = (char*)realloc(data, total_size + str_size);
			if (temp == NULL)
			{
				has_error = true;
				break;
			}
			data = temp;
		}
		if (data == NULL) break;
		memcpy(data + total_size, temp->value, str_size);
		total_size += str_size;
		node = node->next;
	} 

	if (has_error == true)
	{
		free(data);
		data = NULL;
		return NULL;
	}

	return init_string(data, total_size);
}

void free_string_builder(string_builder* sb_ptr)
{
	if (sb_ptr == NULL) return;
	free_list(sb_ptr->list);
	destroy_string_builder(sb_ptr);
	sb_ptr = NULL;
}