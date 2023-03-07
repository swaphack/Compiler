#include "syntax_tree.h"
#include "data/macros.h"
#include "collections/extensions.h"

CONSTRUCT_STRUCT(syntax_tree);


syntax_tree* init_syntax_tree()
{
	syntax_tree* st_ptr = create_syntax_tree();
	if (st_ptr == NULL) return NULL;
	st_ptr->token_tree = init_binary_tree();
	return st_ptr;
}
void free_syntax_tree(syntax_tree* st_ptr)
{
	if (st_ptr == NULL) return;
	free_binary_tree(st_ptr->token_tree);
	st_ptr->token_tree = NULL;
	destroy_syntax_tree(st_ptr);
	st_ptr = NULL;
}

void syntax_analysis_parse(syntax_tree* st_ptr, vector* tokens)
{
	if (st_ptr == NULL || tokens == NULL) return;

	for (int i = 0; i < tokens->size; i++)
	{
	}
}