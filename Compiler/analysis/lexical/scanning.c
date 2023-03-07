#include "scanning.h"
#include "collections/hash.h"
#include "data/public_data.h"
#include "analysis/project_code.h"
#include "collections/extensions.h"


CONSTRUCT_STRUCT(lexical_sentence);
CONSTRUCT_STRUCT(lexical_block);

lexical_sentence* init_lexical_sentence()
{
	lexical_sentence* ls_ptr = create_lexical_sentence();
	if (ls_ptr == NULL) return NULL;
	ls_ptr->tokens = init_string_vector();
	ls_ptr->text = init_empty_string();
	return ls_ptr;
}

void free_lexical_sentence(lexical_sentence* ls_ptr)
{
	if (ls_ptr == NULL) return;
	free_vector(ls_ptr->tokens);
	free_string(ls_ptr->text);
	destroy_lexical_sentence(ls_ptr);
	ls_ptr = NULL;
}

void del_lexical_sentence(void* a)
{
	lexical_sentence* aa = (lexical_sentence*)a;
	free_lexical_sentence(aa);
}

int compare_lexical_sentence(void* a, void* b)
{
	lexical_sentence* aa = (lexical_sentence*)a;
	lexical_sentence* bb = (lexical_sentence*)b;
	return compare_string(aa->text, bb->text);
}

void del_lexical_block(void* a)
{
	lexical_block* aa = (lexical_block*)a;
	free_lexical_block(aa);
}

int compare_lexical_block(void* a, void* b)
{
	lexical_block* aa = (lexical_block*)a;
	lexical_block* bb = (lexical_block*)b;
	if (aa->index < bb->index) return -1;
	else if (aa->index > bb->index) return 1;
	return 0;
}

lexical_block* init_lexical_block()
{
	lexical_block* ll_ptr = create_lexical_block();
	if (ll_ptr == NULL) return NULL;
	ll_ptr->sentences = init_list_with_func(compare_lexical_sentence, del_lexical_sentence);
	ll_ptr->blocks = init_list_with_func(compare_lexical_block, del_lexical_block);
	return ll_ptr;
}
void free_lexical_block(lexical_block* ll_ptr)
{
	if (ll_ptr == NULL) return;
	free_list(ll_ptr->sentences);
	free_list(ll_ptr->blocks);
	destroy_lexical_block(ll_ptr);
	ll_ptr = NULL;
}

bool is_number_string(const string* data)
{
	if (data == NULL || data->size == 0) return false;

	for (int i = 0; i < data->size; i++)
	{
		char c = data->value[i];
		if (!IS_NUMBER_CHAR(c)) return false;
	}

	return true;
}

bool is_letter_string(const string* data)
{
	if (data == NULL || data->size == 0) return false;

	for (int i = 0; i < data->size; i++)
	{
		char c = data->value[i];
		if (!IS_LETTER_CHAR(c)) return false;
	}

	return true;
}

bool is_variable_string(const string* data)
{
	if (data == NULL || data->size == 0) return false;

	bool ret = false;
	do
	{
		char first = data->value[0];
		ret = first == '_' || IS_LETTER_CHAR(first);
		if (!ret) break;
		for (int i = 1; i < data->size; i++)
		{
			char c = data->value[i];
			ret = IS_VARIABLE_CHAR(c);
			if (!ret) break;
		}
	} while (0);

	return ret;
}