#include "symbol_table.h"
#include "collections/hash.h"

CONSTRUCT_STRUCT(symbol_table);
CONSTRUCT_STRUCT(symbol_data);

symbol_data* init_symbol_data(const char* name)
{
	return init_symbol_data_with_type(name, NULL);
}

symbol_data* init_symbol_data_with_type(const char* name, const char* type)
{
	symbol_data* data = create_symbol_data();
	if (data == NULL) return NULL;

	if (name != NULL)
	{
		data->name = init_hash_c_string(name);
	}
	if (type != NULL)
	{
		data->type = init_c_string(type);
	}
	return data;
}
void free_symbol_data(symbol_data* data)
{
	if (data == NULL) return;

	if (data->name != NULL)
	{
		free_hash_string(data->name);
		data->name = NULL;
	}
	if (data->type != NULL)
	{
		free_string(data->type);
		data->type = NULL;
	}
	destroy_symbol_data(data);
}

int compare_symbol(void* a, void* b)
{
	symbol_data* aa = (symbol_data*)a;
	symbol_data* bb = (symbol_data*)b;
	return compare_hash_string(aa->name, bb->name);
}

void del_symbol(void* a)
{
	symbol_data* data = (symbol_data*)a;
	if (data->name != NULL)
	{
		free_hash_string(data->name);
		data->name = NULL;
	}
	free_symbol_data(data);
	data = NULL;
}

symbol_table* init_symbol_table()
{
	symbol_table* st_ptr = create_symbol_table();
	st_ptr->sysmbols = init_vector();
	st_ptr->sysmbols->compare = compare_symbol;
	st_ptr->sysmbols->del = del_symbol;
	return st_ptr;
}

void symbol_table_add_data(symbol_table* st_ptr, symbol_data* data)
{
	if (st_ptr == NULL || data == NULL ) return;
	if (data->name == NULL || data->name->value == NULL) return;

	vector_add_data(st_ptr->sysmbols, data);
}
void symbol_table_remove_data(symbol_table* st_ptr, const char* name)
{
	if (st_ptr == NULL || name == NULL) return;
	symbol_data* data = init_symbol_data(name);
	vector_remove_data(st_ptr->sysmbols, &data);
	free_symbol_data(data);
}

int symbol_table_index_of_data(symbol_table* st_ptr, const char* name)
{
	if (st_ptr == NULL || name == NULL) return -1;
	symbol_data* data = init_symbol_data(name);
	int index = vector_index_of(st_ptr->sysmbols, &data);
	free_symbol_data(data);

	return index;
}

symbol_data* symbol_table_get_data(symbol_table* st_ptr, int index)
{
	if (st_ptr == NULL || index < 0 || index >= st_ptr->sysmbols->size) return NULL;

	void* result = vector_get_data(st_ptr->sysmbols, index);
	return (symbol_data*)result;
}

symbol_data* symbol_table_find_data(symbol_table* st_ptr, const char* name)
{
	if (st_ptr == NULL || name == NULL) return NULL;
	symbol_data* data = init_symbol_data(name);
	int index = vector_index_of(st_ptr->sysmbols, &data);
	free_symbol_data(data);

	if (index == -1) return NULL;

	void* result = vector_get_data(st_ptr->sysmbols, index);
	return (symbol_data*)result;
}

void free_symbol_table(symbol_table* st_ptr)
{
	if (st_ptr == NULL) return;
	free_vector(st_ptr->sysmbols);
	free(st_ptr);
	st_ptr = NULL;
}

