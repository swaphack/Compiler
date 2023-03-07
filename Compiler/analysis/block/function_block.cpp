#include "function_block.h"
#include "scope_info.h"
#include "variable_block.h"

CONSTRUCT_STRUCT(function_block);

void del_map_string_function_block(void* key, void* value)
{
	free_string((string*)key);
	free_function_block((function_block*)value);
}

function_block* init_function_block()
{
	function_block* fb_ptr = create_function_block();
	fb_ptr->input_params = init_vector();
	if (fb_ptr->input_params != NULL)
	{
		fb_ptr->input_params->compare = compare_variable_block;
		fb_ptr->input_params->del = del_variable_block;
	}
	fb_ptr->scope_info = init_scope_info();

	return fb_ptr;
}
void free_function_block(function_block* fb_ptr)
{
	if (fb_ptr == NULL) return;
	if (fb_ptr->input_params != NULL)
	{
		free_vector(fb_ptr->input_params);
		fb_ptr->input_params = NULL;
	}

	if (fb_ptr->scope_info != NULL)
	{
		free_scope_info(fb_ptr->scope_info);
		fb_ptr->scope_info = NULL;
	}

	free_string(fb_ptr->name);
	fb_ptr->name = NULL;
	free_string(fb_ptr->code);
	fb_ptr->code = NULL;
	free_string(fb_ptr->return_type);
	fb_ptr->return_type = NULL;

	destroy_function_block(fb_ptr);
	fb_ptr = NULL;
}

void del_function_block(void* a)
{
	function_block* aa = (function_block*)a;
	free_function_block(aa);
}

int compare_function_block(void* a, void* b)
{
	function_block* aa = (function_block*)a;
	function_block* bb = (function_block*)b;

	int ret = compare_string(aa->name, bb->name);
	if (ret != 0) return ret;

	if (aa->input_params->size < bb->input_params->size) return -1;
	if (aa->input_params->size > bb->input_params->size) return 1;
	int len = aa->input_params->size;
	for (int i = 0; i < len; i++)
	{
		variable_block* da = (variable_block*)vector_get_data(aa->input_params, i);
		variable_block* db = (variable_block*)vector_get_data(bb->input_params, i);
		int ret = compare_string(da->type, db->type);
		if (ret != 0) return ret;
	}
	return 0;
}

bool function_block_match_input_params(function_block* fb_ptr, struct variable_block** arguments, int count)
{
	if (fb_ptr == NULL) return false;
	if (fb_ptr->input_params == NULL) return false;
	if (fb_ptr->input_params->size != count) return false;
	if (fb_ptr->input_params->size == 0) return true;
	if (arguments == NULL) return false;

	vector* input_params = fb_ptr->input_params;
	for (int i = 0; i < count; i++)
	{
		variable_block* a = (variable_block*)vector_get_data(input_params, i);
		variable_block* b = arguments[i];
		if (a == NULL || b == NULL)
		{
			return false;
		}

		bool match = compare_string(a->type, b->type) && a->delivery_type == b->delivery_type;
		if (!match)
		{
			return false;
		}
	}

	return true;
}

bool function_block_call(function_block* fb_ptr, struct variable_block** arguments, int count, struct variable_block* return_value)
{
	if (fb_ptr == NULL) return false;

	if (!function_block_match_input_params(fb_ptr, arguments, count)) return false;

	// 执行代码
	if (fb_ptr->code == NULL) return false;


	return false;
}

void function_block_code_parse(function_block* fb_ptr)
{
	if (fb_ptr == NULL) return;
	// 执行代码
	if (fb_ptr->code == NULL) return;
}

void function_block_add_input_param(function_block* fb_ptr, struct variable_block* vb_ptr)
{
	if (fb_ptr == NULL || vb_ptr == NULL) return;

	scope_info_init_with(vb_ptr->scope_info, est_function, fb_ptr);
	vector_add_data(fb_ptr->input_params, vb_ptr);
}
void function_block_remove_input_param(function_block* fb_ptr, string* name)
{
	if (fb_ptr == NULL || name == NULL) return;

	variable_block vb;
	vb.name = name;
	vector_remove_data(fb_ptr->input_params, &vb);
}
struct variable_block* function_block_get_input_param(function_block* fb_ptr, string* name)
{
	if (fb_ptr == NULL || name == NULL) return NULL;

	variable_block vb;
	vb.name = name;
	void* value = vector_find_data(fb_ptr->input_params, &vb);
	return (variable_block*)value;
}
