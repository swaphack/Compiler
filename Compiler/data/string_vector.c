#include "string_vector.h"
#include "collections/extensions.h"

CONSTRUCT_STRUCT(vector_string);

vector_string* init_vector_string()
{
	vector_string* vs_ptr = create_vector_string();
	if (vs_ptr == NULL) return NULL;
	vs_ptr->strings = init_string_vector();

	return vs_ptr;
}
void vector_string_init_with(vector_string* vs_ptr, string** strings, int count)
{
	if (vs_ptr == NULL || strings == NULL || count == 0) return;

	for (int i = 0; i < count; i++)
	{
		vector_add_data(vs_ptr->strings, clone_string(strings[i]));
	}
}

void free_vector_string(vector_string* vs_ptr)
{
	if (vs_ptr == NULL) return;
	if (vs_ptr->strings != NULL)
	{
		free_vector(vs_ptr->strings);
		vs_ptr->strings = NULL;
	}
	vector_string_free_string_stream(vs_ptr);
	destroy_vector_string(vs_ptr);
}

string* vector_string_get_cur_string(vector_string* vs_ptr)
{
	if (vs_ptr == NULL) return NULL;
	if (vs_ptr->strings == NULL) return NULL;
	if (vs_ptr->over == true) return NULL;
	if ((vs_ptr->index > 0) && (vs_ptr->index <= vs_ptr->strings->size - 1))
	{
		return (string*)vector_get_data(vs_ptr->strings, vs_ptr->index);
	}
	return NULL;
}

string_stream* vector_string_get_string_stream(vector_string* vs_ptr)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL) return NULL;
	if (vs_ptr->stream != NULL) return vs_ptr->stream;

	string* data = vector_string_get_cur_string(vs_ptr);
	if (data == NULL) return NULL;

	vs_ptr->stream = init_string_stream();
	string_stream_init_with(vs_ptr->stream, data, 0);
	return vs_ptr->stream;
}
char vector_string_read_next_char(vector_string* vs_ptr)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL) return NUL_CHAR;
	if (vs_ptr->over == true) return NUL_CHAR;
	string* data = vector_string_read_string(vs_ptr, 1);
	if (data == NULL || data->value == NULL || data->size == 0) return NUL_CHAR;
	char c = string_char_at(data, 0);
	free_string(data);

	return c;
}
string* vector_string_read_string(vector_string* vs_ptr, int size)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL) return NULL;
	if (vs_ptr->over == true) return NULL;

	string* data = init_empty_string();
	while (size > 0 && !vs_ptr->over)
	{
		string_stream* cur_node = vector_string_get_string_stream(vs_ptr);
		if (cur_node == NULL)
		{
			bool ret = vector_string_move_next(vs_ptr);
			if (!ret) break;
		}

		string* temp = NULL;
		if (string_stream_can_read(vs_ptr->stream, size))
		{
			temp = string_stream_read(vs_ptr->stream, size);
			size -= size;
		}
		else
		{
			int count = vs_ptr->stream->string->size - vs_ptr->stream->cursor;
			temp = string_stream_read(vs_ptr->stream, count);
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
string* vector_string_read_next_string(vector_string* vs_ptr)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL) return NULL;
	if (vs_ptr->over == true) return NULL;

	bool ret = vector_string_move_next(vs_ptr);
	if (!ret) return NULL;

	string* data = vector_string_get_cur_string(vs_ptr);
	return data;
}

void vector_string_free_string_stream(vector_string* vs_ptr)
{
	if (vs_ptr == NULL) return;
	if (vs_ptr->stream != NULL)
	{
		free_string_stream(vs_ptr->stream);
		vs_ptr->stream = NULL;
	}
}
void vector_string_set_index(vector_string* vs_ptr, int index)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL) return;
	if (vs_ptr->index == index) return;
	vector_string_free_string_stream(vs_ptr);

	int size = vs_ptr->strings->size;
	if (index < 0)  index = 0;
	if (index >= size) index = size;

	vs_ptr->index = index;
	vs_ptr->over = index == size;
}

bool vector_string_move_next(vector_string* vs_ptr)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL || vs_ptr->strings->size == 0) return false;
	vector_string_free_string_stream(vs_ptr);
	if (vs_ptr->over) return false;
	string* data = vector_string_get_cur_string(vs_ptr);
	if (data == NULL)
	{
		vs_ptr += 1;
		data = vector_string_get_cur_string(vs_ptr);
	}

	if (data == NULL)
	{
		vs_ptr->over = true;
		return false;
	}

	vector_string_get_string_stream(vs_ptr);

	return true;
}

string* combine_vector_string(vector_string* vs_ptr, string* spilt)
{
	if (vs_ptr == NULL || vs_ptr->strings == NULL || spilt == NULL) return NULL;

	int ssize = 0;
	if (spilt != NULL)
	{
		ssize = spilt->size;
	}
	int count = vs_ptr->strings->size;
	int size = ssize * (count - 1);
	for (int i = 0; i < count; i++)
	{
		string* str = (string*)vector_get_data(vs_ptr->strings, i);
		if (str != NULL)
		{
			size += str->size;
		}
	}

	int offset = 0;
	char* temp = str_malloc(size + 1);
	if (temp == NULL) return NULL;
	for (int i = 0; i < count; i++)
	{
		string* str = (string*)vector_get_data(vs_ptr->strings, i);
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
