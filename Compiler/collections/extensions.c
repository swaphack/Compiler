#include "extensions.h"
#include "data/string_data.h"

int compare_string_key(void* a, void* b)
{
	string* aa = (string*)a;
	string* bb = (string*)b;

	return compare_string(aa, bb);
}

void del_map_string_key(void* a, void* b)
{
	free_string((string*)a);
	free_string((string*)b);
}

void del_string_key(void* a)
{
	string* aa = (string*)a;
	free_string(aa);
}

map* init_map_with_string_key(void (*del)(void* key, void* value))
{
	map* ptr = init_map_with_func(compare_string_key, del);
	return ptr;
}

map* init_string_map()
{
	map* ptr = init_map_with_func(compare_string_key, del_map_string_key);
	return ptr;
}

list* init_string_list()
{
	list* ptr = init_list_with_func(compare_string_key, del_string_key);
	return ptr;
}

vector* init_string_vector()
{
	vector* ptr = init_vector_with_func(compare_string_key, del_string_key);
	return ptr;
}