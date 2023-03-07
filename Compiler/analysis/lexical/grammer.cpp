#include "grammer.h"

#include "data/string_data.h"
#include "analysis/analysis_table.h"

bool is_terminal_word(const string* word, analysis_table* st_ptr)
{
	if (word == NULL || st_ptr == NULL) return false;

	symbol_data* value = symbol_table_find_data(st_ptr->sign_table, word->value);
	if (value != NULL) return true;
	value = symbol_table_find_data(st_ptr->key_table, word->value);
	if (value != NULL) return true;
	return false;
}

bool is_nonterminal_word(const string* word, analysis_table* st_ptr)
{
	if (word == NULL || st_ptr == NULL) return false;

	symbol_data* value = symbol_table_find_data(st_ptr->struct_table, word->value);
	if (value != NULL) return true;
	value = symbol_table_find_data(st_ptr->function_table, word->value);
	if (value != NULL) return true;
	return false;
}
