#include "string_list.h"
#include "collections/extensions.h"

CONSTRUCT_STRUCT(list_string);


list_string* init_list_string()
{
	list_string* ls_ptr = create_list_string();
	if (ls_ptr == NULL) return NULL;
	ls_ptr->strings = init_string_list();

	return ls_ptr;
}
void list_string_init_with(list_string* ls_ptr, list* strings)
{
	if (ls_ptr == NULL || strings == NULL) return;

	if (ls_ptr->strings != NULL)
	{
		free_list(ls_ptr->strings);
		ls_ptr->strings = NULL;
	}
	ls_ptr->strings = strings;
}
void free_list_string(list_string* ls_ptr)
{
	if (ls_ptr == NULL) return;
	if (ls_ptr->strings != NULL)
	{
		free_list(ls_ptr->strings);
		ls_ptr->strings = NULL;
	}
	list_string_free_string_stream(ls_ptr);
	destroy_list_string(ls_ptr);
}

list_node* list_string_get_cur_node(list_string* ls_ptr)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL) return NULL;
	if (ls_ptr->node != NULL) return ls_ptr->node;
	if (ls_ptr->over == true) return NULL;
	ls_ptr->node = ls_ptr->node;
	return ls_ptr->node;
}

char list_string_read_next_char(list_string* ls_ptr)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL) return NUL_CHAR;
	if (ls_ptr->over == true) return NUL_CHAR;
	string* data = list_string_read_string(ls_ptr, 1);
	if (data == NULL || data->value == NULL || data->size == 0) return NUL_CHAR;
	char c = string_char_at(data, 0);
	free_string(data);

	return c;
}

string* list_string_read_string(list_string* ls_ptr, int size)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL) return NULL;
	if (ls_ptr->over == true) return NULL;
	
	string* data = init_empty_string();
	while (size > 0 && !ls_ptr->over)
	{
		list_node* cur_node = list_string_get_cur_node(ls_ptr);
		if (cur_node == NULL)
		{
			bool ret = list_string_move_next(ls_ptr);
			if (!ret) break;
		}

		string* temp = NULL;
		if (string_stream_can_read(ls_ptr->stream, size))
		{
			temp = string_stream_read(ls_ptr->stream, size);
			size -= size;
		}
		else
		{
			int count = ls_ptr->stream->string->size - ls_ptr->stream->cursor;
			temp = string_stream_read(ls_ptr->stream, count);
			if (temp == NULL) break;
			size -= count;
		}
		if (temp != NULL)
		{
			string_append_string(data, temp);
			free_string(temp);
		}
		
		if (size <= 0) break;
	}

	return data;
}

string* list_string_read_next_string(list_string* ls_ptr)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL) return NULL;
	if (ls_ptr->over == true) return NULL;

	bool ret = list_string_move_next(ls_ptr);
	if (!ret) return NULL;

	list_node* cur_node = list_string_get_cur_node(ls_ptr);
	if (cur_node == NULL)
	{
		return NULL;
	}
	return (string*)cur_node->data;
}

string_stream* list_string_get_string_stream(list_string* ls_ptr)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL) return NULL;
	if (ls_ptr->stream != NULL) return ls_ptr->stream;

	list_node* node = list_string_get_cur_node(ls_ptr);
	if (node == NULL) return NULL;

	string* data = (string*)node->data;
	if (data == NULL) return NULL;

	ls_ptr->stream = init_string_stream();
	string_stream_init_with(ls_ptr->stream, data, 0);
	return ls_ptr->stream;
}

void list_string_free_string_stream(list_string* ls_ptr)
{
	if (ls_ptr == NULL) return;
	if (ls_ptr->stream != NULL)
	{
		free_string_stream(ls_ptr->stream);
		ls_ptr->stream = NULL;
	}
}

void list_string_set_node(list_string* ls_ptr, list_node* node)
{
	if (ls_ptr == NULL) return;
	if (ls_ptr->node == node) return;
	list_string_free_string_stream(ls_ptr);

	ls_ptr->node = node;
	ls_ptr->over = node == NULL;
}

bool list_string_move_next(list_string* ls_ptr)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL || ls_ptr->strings->root == NULL) return false;
	list_string_free_string_stream(ls_ptr);
	if (ls_ptr->over) return false;
	list_node* node = list_string_get_cur_node(ls_ptr);
	if (node == NULL)
	{
		node = ls_ptr->strings->root;
	}
	else
	{
		node = node->next;
	}	

	ls_ptr->node = node;
	if (node == NULL)
	{
		ls_ptr->over = true;
		return false;
	}

	list_string_get_string_stream(ls_ptr);

	return true;
}

string* combine_list_string(list_string* ls_ptr, string* spilt)
{
	if (ls_ptr == NULL || ls_ptr->strings == NULL || spilt == NULL) return NULL;

	int ssize = 0;
	if (spilt != NULL)
	{
		ssize = spilt->size;
	}
	int count = list_get_size(ls_ptr->strings);
	int size = 0; 

	list_node* node = ls_ptr->strings->root;
	while (node != NULL)
	{
		string* str = (string*)node->data;
		if (str != NULL)
		{
			size += str->size;
		}
		node = node->next;
	}

	size += ssize * (count - 1);

	int offset = 0;
	char* temp = str_malloc(size + 1);
	if (temp == NULL) return NULL;

	node = ls_ptr->strings->root;
	while (node != NULL)
	{
		if ((ssize > 0) && (node != ls_ptr->strings->root))
		{
			memcpy(temp + offset, spilt->value, ssize);
			offset += ssize;
		}

		string* str = (string*)node->data;
		if (str != NULL)
		{
			memcpy(temp + offset, str->value, str->size);
			offset += str->size;
		}
		node = node->next;
	}

	return init_string_with_free(temp, size);
}