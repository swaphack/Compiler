#include "lexical_analysis.h"
#include "analysis/project_code.h"
#include "data/public_data.h"
#include "stream/string_stream.h"
#include "analysis/analysis_table.h"
#include "data/string_builder.h"
#include <stdio.h>

CONSTRUCT_STRUCT(lexical_analysis);

lexical_analysis* init_lexical_analysis()
{
	lexical_analysis* la_ptr = create_lexical_analysis();
	if (la_ptr == NULL) return NULL;
	return la_ptr;
}

void free_lexical_analysis(lexical_analysis* la_ptr)
{
	if (la_ptr == NULL) return;
	free_string(la_ptr->filepath);
	destroy_lexical_analysis(la_ptr);
	la_ptr = NULL;
}

bool find_invalid_data(void* a, void* b)
{
	string* aa = (string*)a;
	string_stream* bb = (string_stream*)b;
	return string_stream_equal_string(bb, aa);
}

void lexical_analysis_filter_invalid_words(lexical_analysis* la_ptr, struct code_file* cf_ptr)
{
	if (la_ptr == NULL || cf_ptr == NULL) return;

	analysis_table* at_ptr = la_ptr->table_ptr;
	if (at_ptr == NULL) return;
	list* it_ptr =  at_ptr->invalid_table;
	if (it_ptr == NULL || it_ptr->root == NULL) return;

	string* text = cf_ptr->text;
	if (string_is_null_or_empty(text)) return;
	
	string_stream* ss_ptr = init_string_stream();
	if (ss_ptr == NULL) return;

	string_stream_init_with_ptr(ss_ptr, text, 0);

	string_builder* sb_ptr = init_string_builder();
	do
	{
		string* data = (string*)list_find_if(it_ptr, find_invalid_data, ss_ptr);
		if (data != NULL)
		{
			string_stream_move(ss_ptr, data->size);
		}
		else
		{
			char c = string_stream_char_at_cursor(ss_ptr);
			string_builder_append_char(sb_ptr, 1, c);
			string_stream_move(ss_ptr, 1);
		}
		bool ret = string_stream_is_over(ss_ptr);
		if (ret) break;
	} while (true);
	free_string_stream(ss_ptr);
	free_string(cf_ptr->text);
	cf_ptr->text = string_builder_to_string(sb_ptr);
	free_string_builder(sb_ptr);
}

void lexical_analysis_load_tokens(lexical_analysis* la_ptr, struct code_file* cf_ptr)
{
	if (la_ptr == NULL || cf_ptr == NULL)  return;

	string_stream* ss_ptr = init_string_stream();
	string_stream_init_with(ss_ptr, cf_ptr->text, 0);

	string* token = init_empty_string();
	int offset = ss_ptr->cursor;
	while (!offset < ss_ptr->string->size)
	{
		char c = string_stream_char_at(ss_ptr, offset);
		if (IS_NUL_CHAR(c)) break;

		bool add_front_data = false;
		bool append_data = false;
		bool add_cur_data = false;
		if (IS_LINE_BREAK_CHAR(c))
		{// »»ÐÐ·û
			add_front_data = true;
			append_data = true;
			add_cur_data = true;
		}
		else if (IS_ESCAPE_CHAR(c))
		{
			add_front_data = true;
			append_data = true;
			add_cur_data = true;
		}
		else if (IS_EMPTY_CHAR(c))
		{
			add_front_data = true;
		}
		else if (IS_OPERATOR_CHAR(c) || IS_DELIMITER_CHAR(c))
		{
			add_front_data = true;
			append_data = true;
			add_cur_data = true;
		}
		else if (IS_VARIABLE_CHAR(c) || IS_NUMBER_CHAR(c))
		{
			append_data = true;
		}
		else if (IS_SPECIAL_CHAR(c))
		{
			add_front_data = true;
			append_data = true;
		}
		else if (IS_STRING_CHAR(c))
		{
			add_front_data = true;
			append_data = true;
			//add_cur_data = true;
		}
		else
		{// ÆäËû×Ö·û
			append_data = true;
		}

		if (add_front_data)
		{
			if (token->size > 0)
			{
				list_append_data(cf_ptr->tokens, clone_string(token));
				string_clear(token);
			}
		}

		if (append_data)
		{
			string_append_char(token, 1, c);
		}

		if (add_cur_data)
		{
			if (token->size > 0)
			{
				list_append_data(cf_ptr->tokens, clone_string(token));
				string_clear(token);
			}
		}

		offset++;
	}
	free_string(token);
}

void show_list_string(void* a, void* b)
{
	string* aa = (string*)a;

	printf("%s ", aa->value);
}

void lexical_analysis_scan_code_file(lexical_analysis* la_ptr, struct code_file* cf_ptr)
{
	if (la_ptr == NULL || cf_ptr == NULL) return;

	lexical_analysis_filter_invalid_words(la_ptr, cf_ptr);
	lexical_analysis_load_tokens(la_ptr, cf_ptr);

	list_foreach(cf_ptr->tokens, show_list_string, NULL);



	//lexical_analysis_method* method = la_ptr->analysis_method;
	//if (method == NULL) return;
	//
	//if (method->extract_tokens != NULL)
	//{
	//	method->extract_tokens(la_ptr, cf_ptr->tokens);
	//}
}