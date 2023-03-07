#include "namespace_block.h"
#include "variable_block.h"
#include "function_block.h"
#include "struct_block.h"
#include "scope_info.h"
#include "collections/extensions.h"

CONSTRUCT_STRUCT(namespace_block);

namespace_block* init_namespace_block()
{
	namespace_block* sb_ptr = create_namespace_block();
	if (sb_ptr == NULL) return NULL;
	sb_ptr->const_variables = init_map_with_string_key(del_map_string_variable_block);
	sb_ptr->static_variables = init_map_with_string_key(del_map_string_variable_block);
	sb_ptr->variables = init_map_with_string_key(del_map_string_variable_block);
	sb_ptr->functions = init_map_with_string_key(del_map_string_function_block);
	sb_ptr->structs = init_map_with_string_key(del_map_string_struct_block);
	return sb_ptr;
}

void free_namespace_block(namespace_block* nb_ptr)
{
	if (nb_ptr == NULL) return;
	free_string(nb_ptr->name);
	nb_ptr->name = NULL;

	if (nb_ptr->static_variables != NULL)
	{
		free_map(nb_ptr->static_variables);
		nb_ptr->static_variables = NULL;
	}

	if (nb_ptr->const_variables != NULL)
	{
		free_map(nb_ptr->const_variables);
		nb_ptr->const_variables = NULL;
	}

	if (nb_ptr->variables != NULL)
	{
		free_map(nb_ptr->variables);
		nb_ptr->variables = NULL;
	}

	if (nb_ptr->functions != NULL)
	{
		free_map(nb_ptr->functions);
		nb_ptr->functions = NULL;
	}

	if (nb_ptr->structs != NULL)
	{
		free_map(nb_ptr->structs);
		nb_ptr->structs = NULL;
	}

	destroy_namespace_block(nb_ptr);
	nb_ptr = NULL;
}

void namespace_block_add_const_variable(namespace_block* nb_ptr, variable_block* vb_ptr)
{
	if (nb_ptr == NULL || vb_ptr == NULL) return;

	string* name = clone_string(vb_ptr->name);
	scope_info_init_with(vb_ptr->scope_info, est_namespace, nb_ptr);
	map_add_data(nb_ptr->const_variables, name, vb_ptr);
}
void namespace_block_remove_const_variable(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return;

	map_remove_data(nb_ptr->const_variables, name);
}
variable_block* namespace_block_get_const_variable(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(nb_ptr->const_variables, name);
	return (variable_block*)value;
}

void namespace_block_add_static_variable(namespace_block* nb_ptr, variable_block* vb_ptr)
{
	if (nb_ptr == NULL || vb_ptr == NULL) return;

	string* name = clone_string(vb_ptr->name);
	scope_info_init_with(vb_ptr->scope_info, est_namespace, nb_ptr);
	map_add_data(nb_ptr->static_variables, name, vb_ptr);
}
void namespace_block_remove_static_variable(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return;

	map_remove_data(nb_ptr->static_variables, name);
}
variable_block* namespace_block_get_static_variable(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(nb_ptr->const_variables, name);
	return (variable_block*)value;
}

void namespace_block_add_variable(namespace_block* nb_ptr, variable_block* vb_ptr)
{
	if (nb_ptr == NULL || vb_ptr == NULL) return;

	string* name = clone_string(vb_ptr->name);
	scope_info_init_with(vb_ptr->scope_info, est_namespace, nb_ptr);
	map_add_data(nb_ptr->variables, name, vb_ptr);
}
void namespace_block_remove_variable(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return;

	map_remove_data(nb_ptr->variables, name);
}
variable_block* namespace_block_get_variable(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(nb_ptr->const_variables, name);
	return (variable_block*)value;
}

void namespace_block_add_function(namespace_block* nb_ptr, function_block* fb_ptr)
{
	if (nb_ptr == NULL || fb_ptr == NULL) return;

	string* name = clone_string(fb_ptr->name);
	scope_info_init_with(fb_ptr->scope_info, est_namespace, nb_ptr);
	map_add_data(nb_ptr->functions, name, fb_ptr);
}

void namespace_block_remove_function(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return;

	map_remove_data(nb_ptr->functions, name);
}
function_block* namespace_block_get_function(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(nb_ptr->functions, name);
	return (function_block*)value;
}

void namespace_block_add_struct(namespace_block* nb_ptr, struct struct_block* sb_ptr)
{
	if (nb_ptr == NULL || sb_ptr == NULL) return;

	string* name = clone_string(sb_ptr->name);
	scope_info_init_with(sb_ptr->scope_info, est_namespace, nb_ptr);
	map_add_data(nb_ptr->structs, name, sb_ptr);
}
void namespace_block_remove_struct(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return;

	map_remove_data(nb_ptr->structs, name);
}
struct function_block* namespace_block_get_struct(namespace_block* nb_ptr, string* name)
{
	if (nb_ptr == NULL || name == NULL) return NULL;

	void* value = map_get_value(nb_ptr->structs, name);
	return (function_block*)value;
}