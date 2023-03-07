#include "analysis_error.h"
#include "data/data.h"

CONSTRUCT_STRUCT(analysis_token_unit);
CONSTRUCT_STRUCT(analysis_error);

int compare_analysis_token_unit(void* a, void* b)
{
	analysis_token_unit* aa = (analysis_token_unit*)a;
	analysis_token_unit* bb = (analysis_token_unit*)b;

	int ret = compare_string(aa->filepath, bb->filepath);
	if (ret != 0) return ret;
	ret = compare_int(aa->line, bb->line);
	return ret;
}

void del_analysis_token_unit(void* a)
{
	analysis_token_unit* aa = (analysis_token_unit*)a;

	free_analysis_token_unit(aa);
}


analysis_token_unit* init_analysis_token_unit()
{
	analysis_token_unit* atu_ptr = create_analysis_token_unit();
	return atu_ptr;
}
void free_analysis_token_unit(analysis_token_unit* atu_ptr)
{
	if (atu_ptr == NULL) return;

	destroy_analysis_token_unit(atu_ptr);
	atu_ptr = NULL;
}

analysis_error* init_analysis_error()
{
	analysis_error* ae_ptr = create_analysis_error();
	if (ae_ptr == NULL) return NULL;

	ae_ptr->lexical_err = init_list_with_func(compare_analysis_token_unit, del_analysis_token_unit);
	ae_ptr->syntax_err = init_list_with_func(compare_analysis_token_unit, del_analysis_token_unit);

	return ae_ptr;
}

void free_analysis_error(analysis_error* ae_ptr)
{
	if (ae_ptr == NULL) return;
	if (ae_ptr->lexical_err != NULL)
	{
		free_list(ae_ptr->lexical_err);
		ae_ptr->lexical_err = NULL;
	}
	if (ae_ptr->syntax_err != NULL)
	{
		free_list(ae_ptr->syntax_err);
		ae_ptr->syntax_err = NULL;
	}
	destroy_analysis_error(ae_ptr);
	
	ae_ptr = NULL;
}

void analysis_error_add_lexical_unit(analysis_error* ae_ptr, analysis_token_unit* atu_ptr)
{
	if (ae_ptr == NULL || atu_ptr == NULL) return;

	list_append_data(ae_ptr->lexical_err, atu_ptr);

}
void analysis_error_add_syntax_unit(analysis_error* ae_ptr, analysis_token_unit* atu_ptr)
{
	if (ae_ptr == NULL || atu_ptr == NULL) return;

	list_append_data(ae_ptr->syntax_err, atu_ptr);
}