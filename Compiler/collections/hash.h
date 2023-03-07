#pragma once

#include "data/macros.h"
#include "data/string_data.h"
#include "list.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hash_node
{
	uint64_t hash;
	string* name;
	void* data;
}hash_node;

typedef struct hash_table
{
	int mod;
	list** list;
}hash_table;


uint64_t get_hash_code(const char* key);

hash_table* init_hash_table();
void hash_table_resize(hash_table* hash_ptr, int mod);
bool hash_table_contains_data(hash_table* hash_ptr, const char* name);
void hash_table_add_data(hash_table* hash_ptr, const char* name, void* data);
void hash_table_remove_data(hash_table* hash_ptr, const char* name);
void hash_table_clear(hash_table* hash_ptr);
void free_hash_table(hash_table* hash_ptr);


#ifdef __cplusplus
}
#endif