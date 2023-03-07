#include "analysis_table_c.h"

#include "analysis/analysis_table.h"
#include "analysis/symbol_table.h"
#include "data/public_data.h"

#define ADD_SYMBOL_DATA(ptr, name) symbol_table_add_data(ptr, init_symbol_data(name));

void init_analysis_table_with_c(struct analysis_table* at_ptr)
{
	if (at_ptr == NULL) return;

	symbol_table* st_ptr = at_ptr->preprocess_table;
	if (st_ptr != NULL)
	{
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_DEFINE);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_STRING);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_CONCATE);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_ARGS);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_VAR_ARGS);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_UNDEF);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_IFDEF);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_ELSE);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_ENDIF);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_IFNDEF);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_IF);
		ADD_SYMBOL_DATA(st_ptr, C_PREPROCESS_ELIF);
	}

	st_ptr = at_ptr->key_table;
	if (st_ptr != NULL)
	{
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_CHAR);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_DOUBLE);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_ENUM);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_FLOAT);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_INT);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_LONG);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_SHORT);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_SIGNED);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_STRUCT);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_UNION);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_UNSIGNED);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_VOID);

		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_FOR);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_DO);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_WHILE);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_BREAK);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_CONTINUE);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_IF);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_ELSE);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_GOTO);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_SWITCH);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_CASE);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_DEFAULT);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_RETURN);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_AUTO);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_EXTERN);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_REGISTER);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_STATIC);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_CONST);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_SIZEOF);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_TYPEDEF);
		ADD_SYMBOL_DATA(st_ptr, C_KEY_WORD_VOLATILE);
	}

	st_ptr = at_ptr->sign_table;
	if (st_ptr != NULL)
	{
		ADD_SYMBOL_DATA(st_ptr, STRING_LEFT_PARENTHESES);
		ADD_SYMBOL_DATA(st_ptr, STRING_RIGHT_PARENTHESES);
		ADD_SYMBOL_DATA(st_ptr, STRING_LEFT_BRACKETS);
		ADD_SYMBOL_DATA(st_ptr, STRING_RIGHT_BRACKETS);
		ADD_SYMBOL_DATA(st_ptr, STRING_OPENING_BRACES);
		ADD_SYMBOL_DATA(st_ptr, STRING_CLOSING_BRACES);
		ADD_SYMBOL_DATA(st_ptr, STRING_COMMA);
		ADD_SYMBOL_DATA(st_ptr, STRING_SEMICOLON);
		ADD_SYMBOL_DATA(st_ptr, STRING_MUL);
		ADD_SYMBOL_DATA(st_ptr, STRING_SUB);
		ADD_SYMBOL_DATA(st_ptr, STRING_ADD);
		ADD_SYMBOL_DATA(st_ptr, STRING_DIV);
		ADD_SYMBOL_DATA(st_ptr, STRING_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_MUL_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_SUB_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_ADD_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_DIV_ASSIGN);

		ADD_SYMBOL_DATA(st_ptr, STRING_AUTO_ADD);
		ADD_SYMBOL_DATA(st_ptr, STRING_AUTO_SUB);
		ADD_SYMBOL_DATA(st_ptr, STRING_MOD);
		ADD_SYMBOL_DATA(st_ptr, STRING_NOT);

		ADD_SYMBOL_DATA(st_ptr, STRING_GREATER);
		ADD_SYMBOL_DATA(st_ptr, STRING_GEQUAL);
		ADD_SYMBOL_DATA(st_ptr, STRING_LESS);
		ADD_SYMBOL_DATA(st_ptr, STRING_LEQUAL);

		ADD_SYMBOL_DATA(st_ptr, STRING_EQUAL);
		ADD_SYMBOL_DATA(st_ptr, STRING_NOT_EQUAL);
		ADD_SYMBOL_DATA(st_ptr, STRING_QUESTION);
		ADD_SYMBOL_DATA(st_ptr, STRING_QUESTION_CONDTION);

		ADD_SYMBOL_DATA(st_ptr, STRING_AND);
		ADD_SYMBOL_DATA(st_ptr, STRING_OR);

		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_OR);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_AND);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_XOR);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_COMPLEMENT);

		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_OR_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_AND_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_XOR_ASSIGN);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_COMPLEMENT_ASSIGN);

		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_SHIFT_LEFT);
		ADD_SYMBOL_DATA(st_ptr, STRING_BIT_SHIFT_RIGHT);

		ADD_SYMBOL_DATA(st_ptr, STRING_PERIOD);
		ADD_SYMBOL_DATA(st_ptr, STRING_STRUCT_PTR);
	}

	map* map_ptr = at_ptr->block_table;
	if (map_ptr != NULL)
	{
		map_add_data(map_ptr, init_c_string(STRING_LEFT_PARENTHESES), init_c_string(STRING_RIGHT_PARENTHESES));
		map_add_data(map_ptr, init_c_string(STRING_LEFT_BRACKETS), init_c_string(STRING_RIGHT_BRACKETS));
		map_add_data(map_ptr, init_c_string(STRING_OPENING_BRACES), init_c_string(STRING_CLOSING_BRACES));
	}

	list* list_ptr = at_ptr->invalid_table;
	if (list_ptr != NULL)
	{
		list_append_data(list_ptr, init_c_string("\r"));
		list_append_data(list_ptr, init_c_string("\t"));
		list_append_data(list_ptr, init_c_string("\v"));
		list_append_data(list_ptr, init_c_string(" "));
	}
}