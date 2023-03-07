#include "scanning_c.h"
#include "data/public_data.h"
#include "data/string_list.h"
#include "analysis/lexical/lexical_analysis.h"
#include "analysis/analysis_table.h"



// ×¢ÊÍ
/*
bool lexical_analysis_extract_c_comment(lexical_block* ll_ptr, char c)
{
	if (ll_ptr == NULL || c == NUL_CHAR) return false;

	if (c != '/') return false;
	return false;
}


bool lexical_analysis_skip_c_invalid_letter(lexical_block* ll_ptr, char c)
{
	if (ll_ptr == NULL || c == NUL_CHAR) return false;


	return false;
}
bool lexical_analysis_extract_c_struct(lexical_block* ll_ptr, list_string* ls_ptr)
{
	if (ll_ptr == NULL || ls_ptr == NULL) return false;


	return false;
}

bool lexical_analysis_extract_c_function(lexical_block* ll_ptr, list_string* ls_ptr)
{
	if (ll_ptr == NULL || ls_ptr == NULL) return NULL;


	return NULL;
}

list_node* lexical_analysis_extract_c_variables(lexical_block* ll_ptr, list_string* ls_ptr)
{
	if (ll_ptr == NULL || ls_ptr == NULL) return NULL;


	return NULL;
}

list_node* lexical_analysis_extract_c_token(lexical_block* ll_ptr, list_string* ls_ptr)
{
	if (ll_ptr == NULL || ls_ptr == NULL) return NULL;


	return NULL;
}

void lexical_analysis_extract_c_tokens(struct lexical_analysis* la_ptr, list* tokens)
{
	if (la_ptr == NULL || tokens == NULL) return;

	//list_clear(method->blocks);
	if (tokens->root == NULL) return;
	
	list_node* node = tokens->root;
	if (node == NULL) return;

	int index = 0;
	lexical_block* ll_ptr = NULL;

	list_string* ls_ptr = init_list_string();
	if (ls_ptr == NULL) return;
	list_string_init_with(ls_ptr, tokens);
	do
	{
		if (ll_ptr == NULL)
		{
			ll_ptr = init_lexical_block();
			if (ll_ptr == NULL) break;
			ll_ptr->index = index;
			index++;
		}
		char c = list_string_read_next_char(ls_ptr);
		if (c == NUL_CHAR) break;

		bool ret = false;
		// ×¢ÊÍ
		ret = lexical_analysis_extract_c_comment(ll_ptr, c);

		if (ret == true)
		{
			//list_append_data(method->blocks, ll_ptr);
		}
		
	} while (true);
}



bool lexical_analysis_extract_c_line_variables(lexical_analysis* la_ptr, string* line)
{
	if (la_ptr == NULL || line == NULL);

	int index = string_first_index(line, STRING_EMPTY, strlen(STRING_EMPTY));
	if (index == -1) return false;

	string* stu_name = sub_string(line, 0, index);
	if (stu_name == NULL) return false;

	symbol_data* stu_data = symbol_table_find_data(la_ptr->struct_table, stu_name->value);
	if (stu_data == NULL)
	{
		free_string(stu_name);
		return false;
	}

	string* remain = sub_string(line, index + 1, line->size - index - 1);
	if (remain == NULL)
	{
		free_string(stu_name);
		return false;
	}

	int wcount = 0;
	string** words = string_split(remain, STRING_COMMA, strlen(STRING_COMMA), &wcount);
	if (words == NULL || wcount == 0)
	{
		free_string(stu_name);
		free_string(remain);
		return false;
	}

	for (int i = 0; i < wcount; i++)
	{
		int index = string_first_index(words[i], STRING_ASSIGN, strlen(STRING_ASSIGN));
		if (index == -1)
		{
			symbol_data* sd_ptr = init_symbol_data(words[i]->value, stu_name->value);
			symbol_table_add_data(la_ptr->identifier_table, sd_ptr);
		}
		else
		{
			int scount = 0;
			string** value = string_split(words[i], STRING_ASSIGN, strlen(STRING_ASSIGN), &scount);
			if (value != NULL && scount == 2)
			{
				symbol_data* sd_ptr = init_symbol_data(value[0]->value, stu_name->value);
				//sd_ptr->value = clone_string(value[1]->value);
				symbol_table_add_data(la_ptr->identifier_table, sd_ptr);
				// ÒÆµ½´ÊËØÌáÈ¡ÖÐ
				lexical_analysis_extract_c_line_token(la_ptr, words[i]);
			}
			if (value != NULL && scount > 0)
			{
				free_string_array(value, scount);
			}
		}
	}
	free_string_array(words, wcount);
	return true;
}

bool lexical_analysis_extract_c_line_token(lexical_analysis* la_ptr, string* line)
{
	if (la_ptr == NULL || line == NULL) return false;

	int offset = 0;
	string* temp = NULL;
	do
	{
		temp = init_empty_string();
		int i = 0;
		int index = -1;
		int type = 0;
		int len = line->size - offset;
		for (i = 0; i < len; i++)
		{
			char c = line->value[offset + i];
			if (!c || IS_ESCAPE_CHAR(c))
			{
				i++;
				break;
			}
			string_append_char(temp, 1, c);
			index = lexical_analysis_token_index(la_ptr, temp, &type);
			if (index == -1)
			{
				i -= 1;
				string_remove_at(temp, temp->size);
				break;
			}
		}
		if (index == -1)
		{
			break;
		}
		lexical_token* token = lexical_analysis_create_token(la_ptr, type, index, temp);
		if (token != NULL)
		{
			//list_append_data(expression->tokens, token);
		}
		free_string(temp);
		temp = NULL;
		offset += i;
	} while (offset < line->size);

	free_string(temp);

	//vector_add_data(la_ptr->expressions, expression);

	return true;
}

*/