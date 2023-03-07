#include "struct_block.h"
#include "collections/extensions.h"
#include "scope_info.h"
#include "variable_block.h"
#include "function_block.h"

CONSTRUCT_STRUCT(struct_block);


void del_map_string_struct_block(void* key, void* value)
{
	free_string((string*)key);
	free_struct_block((struct_block*)value);
}


struct_block* init_struct_block()
{
	struct_block* sb_ptr = create_struct_block();
	if (sb_ptr == NULL) return NULL;
	sb_ptr->const_variables = init_map_with_string_key(del_map_string_variable_block);
	sb_ptr->static_variables = init_map_with_string_key(del_map_string_variable_block);
	sb_ptr->variables = init_map_with_string_key(del_map_string_variable_block);
	sb_ptr->functions = init_map_with_string_key(del_map_string_function_block);
	sb_ptr->scope_info = init_scope_info();
	return sb_ptr;
}

void struct_block_add_const_variable(struct_block* sb_ptr, variable_block* vb_ptr)
{
	if (sb_ptr == NULL || vb_ptr == NULL) return;

	string* name = clone_string(vb_ptr->name);
	scope_info_init_with(vb_ptr->scope_info, est_struct, sb_ptr);
	map_add_data(sb_ptr->const_variables, name, vb_ptr);
}
void struct_block_remove_const_variable(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return;

	map_remove_data(sb_ptr->const_variables, name);
}
variable_block* struct_block_get_const_variable(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(sb_ptr->const_variables, name);
	if (value != NULL) (variable_block*)value;

	struct_inherit* inherit = sb_ptr->inherit;
	while (inherit != NULL)
	{
		struct_block* parent = inherit->parent;
		if (parent == NULL) break;
		value = map_get_value(parent->const_variables, name);
		if (value != NULL) break;
		inherit = parent->inherit;
	}
	return (variable_block*)value;
}

void struct_block_add_static_variable(struct_block* sb_ptr, variable_block* vb_ptr)
{
	if (sb_ptr == NULL || vb_ptr == NULL) return;

	string* name = clone_string(vb_ptr->name);
	scope_info_init_with(vb_ptr->scope_info, est_struct, sb_ptr);
	map_add_data(sb_ptr->static_variables, name, vb_ptr);
}
void struct_block_remove_static_variable(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return;

	map_remove_data(sb_ptr->static_variables, name);
}
variable_block* struct_block_get_static_variable(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(sb_ptr->static_variables, name);
	if (value != NULL) (variable_block*)value;

	struct_inherit* inherit = sb_ptr->inherit;
	while (inherit != NULL)
	{
		struct_block* parent = inherit->parent;
		if (parent == NULL) break;
		value = map_get_value(parent->static_variables, name);
		if (value != NULL) break;
		inherit = parent->inherit;
	}
	return (variable_block*)value;
}

void struct_block_add_variable(struct_block* sb_ptr, variable_block* vb_ptr)
{
	if (sb_ptr == NULL || vb_ptr == NULL) return;

	string* name = clone_string(vb_ptr->name);
	scope_info_init_with(vb_ptr->scope_info, est_struct, sb_ptr);
	map_add_data(sb_ptr->variables, name, vb_ptr);
}

void struct_block_remove_variable(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return;

	map_remove_data(sb_ptr->variables, name);
}
variable_block* struct_block_get_variable(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(sb_ptr->variables, name);
	if (value != NULL) (variable_block*)value;

	struct_inherit* inherit = sb_ptr->inherit;
	while (inherit != NULL)
	{
		struct_block* parent = inherit->parent;
		if (parent == NULL) break;
		value = map_get_value(parent->variables, name);
		if (value != NULL) break;
		inherit = parent->inherit;
	}
	return (variable_block*)value;
}

void struct_block_add_function(struct_block* sb_ptr, function_block* fb_ptr)
{
	if (sb_ptr == NULL || fb_ptr == NULL) return;

	string* name = clone_string(fb_ptr->name);
	scope_info_init_with(fb_ptr->scope_info, est_struct, sb_ptr);
	map_add_data(sb_ptr->functions, name, fb_ptr);
}
void struct_block_remove_function(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return;

	map_remove_data(sb_ptr->functions, name);
}
function_block* struct_block_get_function(struct_block* sb_ptr, string* name)
{
	if (sb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(sb_ptr->functions, name);
	if (value != NULL) (function_block*)value;

	struct_inherit* inherit = sb_ptr->inherit;
	while (inherit != NULL)
	{
		struct_block* parent = inherit->parent;
		if (parent == NULL) break;
		value = map_get_value(parent->functions, name);
		if (value != NULL) break;
		inherit = parent->inherit;
	}
	return (function_block*)value;
}

void free_struct_block(struct_block* sb_ptr)
{
	if (sb_ptr == NULL) return;
	free_string(sb_ptr->name);
	sb_ptr->name = NULL;

	if (sb_ptr->static_variables != NULL)
	{
		free_map(sb_ptr->static_variables);
		sb_ptr->static_variables = NULL;
	}

	if (sb_ptr->const_variables != NULL)
	{
		free_map(sb_ptr->const_variables);
		sb_ptr->const_variables = NULL;
	}

	if (sb_ptr->variables != NULL)
	{
		free_map(sb_ptr->variables);
		sb_ptr->variables = NULL;
	}

	if (sb_ptr->functions != NULL)
	{
		free_map(sb_ptr->functions);
		sb_ptr->functions = NULL;
	}

	if (sb_ptr->scope_info != NULL)
	{
		free_scope_info(sb_ptr->scope_info);
		sb_ptr->scope_info = NULL;
	}

	destroy_struct_block(sb_ptr);
	sb_ptr = NULL;
}




