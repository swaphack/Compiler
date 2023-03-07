#include "analysis_table.h"
#include "data/data.h"
#include "collections/extensions.h"

CONSTRUCT_STRUCT(lexical_token);
CONSTRUCT_STRUCT(analysis_table);

lexical_token* init_lexical_token(char* name, int index)
{
	lexical_token* lt_ptr = create_lexical_token();
	if (name != NULL)
	{
		lt_ptr->name = init_hash_c_string(name);
	}
	lt_ptr->sysmbol_index = index;
	return lt_ptr;

}
void free_lexical_token(lexical_token* lt_ptr)
{
	if (lt_ptr == NULL) return;

	if (lt_ptr->name != NULL)
	{
		free_hash_string(lt_ptr->name);
		lt_ptr->name = NULL;
	}
	if (lt_ptr->lt_name != NULL)
	{
		free_string(lt_ptr->lt_name);
		lt_ptr->lt_name = NULL;
	}
	destroy_lexical_token(lt_ptr);
}

void del_lexical_token(void* a)
{
	lexical_token* data = (lexical_token*)a;
	free_lexical_token(data);
}

int compare_lexical_token(void* a, void* b)
{
	lexical_token* aa = (lexical_token*)a;
	lexical_token* bb = (lexical_token*)b;

	return compare_hash_string(aa->name, bb->name);
}

analysis_table* init_analysis_table()
{
	analysis_table* at_ptr = create_analysis_table();
	if (at_ptr == NULL) return NULL;
	at_ptr->preprocess_table = init_symbol_table();
	at_ptr->sign_table = init_symbol_table();
	at_ptr->key_table = init_symbol_table();
	at_ptr->struct_table = init_symbol_table();
	at_ptr->function_table = init_symbol_table();
	at_ptr->block_table = init_string_map();
	at_ptr->invalid_table = init_string_list();
	return at_ptr;
}

void free_analysis_table(analysis_table* at_ptr)
{
	if (at_ptr == NULL) return;

	if (at_ptr->preprocess_table != NULL)
	{
		free_symbol_table(at_ptr->preprocess_table);
		at_ptr->preprocess_table = NULL;
	}

	if (at_ptr->sign_table != NULL)
	{
		free_symbol_table(at_ptr->sign_table);
		at_ptr->sign_table = NULL;
	}

	if (at_ptr->key_table != NULL)
	{
		free_symbol_table(at_ptr->key_table);
		at_ptr->key_table = NULL;
	}

	if (at_ptr->struct_table != NULL)
	{
		free_symbol_table(at_ptr->struct_table);
		at_ptr->struct_table = NULL;
	}

	if (at_ptr->function_table != NULL)
	{
		free_symbol_table(at_ptr->function_table);
		at_ptr->function_table = NULL;
	}

	if (at_ptr->block_table != NULL)
	{
		free_map(at_ptr->block_table);
		at_ptr->block_table = NULL;
	}
	if (at_ptr->invalid_table != NULL)
	{
		free_list(at_ptr->invalid_table);
		at_ptr->invalid_table = NULL;
	}
	destroy_analysis_table(at_ptr);
}


int lexical_analysis_token_index(analysis_table* at_ptr, string* str, int* type)
{
	if (at_ptr == NULL || str == NULL) return -1;

	int index = symbol_table_index_of_data(at_ptr->preprocess_table, str->value);
	if (index != -1)
	{
		*type = eltt_preprocess;
	}

	// 符号表
	index = symbol_table_index_of_data(at_ptr->sign_table, str->value);
	if (index != -1)
	{
		*type = eltt_key;
	}

	// 关键字表
	index = symbol_table_index_of_data(at_ptr->key_table, str->value);
	if (index != -1)
	{
		*type = eltt_symbol;
	}

	// 函数表
	index = symbol_table_index_of_data(at_ptr->function_table, str->value);
	if (index != -1)
	{
		*type = eltt_function;
	}

	// 类型表
	index = symbol_table_index_of_data(at_ptr->struct_table, str->value);
	if (index != -1)
	{
		*type = eltt_struct;
	}
	return index;
}

lexical_token* lexical_analysis_create_token(analysis_table* at_ptr, int type, int index, string* str)
{
	if (at_ptr == NULL || str == NULL) return NULL;
	if (index == -1 || type == -1) return NULL;

	lexical_token* token = init_lexical_token(str->value, index);
	if (type == eltt_preprocess)
	{
		token->lt_name = init_c_string(TABLE_PREPROCESS_ID);
	}
	else if (type == eltt_key)
	{
		token->lt_name = init_c_string(TABLE_KEY_NAME);
	}
	else if (type == eltt_symbol)
	{
		token->lt_name = init_c_string(TABLE_SYMBOL_NAME);
	}
	else if (type == eltt_function)
	{
		token->lt_name = init_c_string(TABLE_FUNCTION_NAME);
	}
	else if (type == eltt_struct)
	{
		token->lt_name = init_c_string(TABLE_STRUCT_NAME);
	}
	token->table_type = type;

	return token;
}