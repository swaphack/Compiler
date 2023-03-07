#include "variable_block.h"
#include "scope_info.h"
CONSTRUCT_STRUCT(variable_block);

variable_block* init_variable_block()
{
	variable_block* vb_ptr = create_variable_block();
	if (vb_ptr == NULL) return NULL;
	vb_ptr->alias = init_vector_string();
	vb_ptr->scope_info = init_scope_info();
	return vb_ptr;
}
void free_variable_block(variable_block* vb_ptr)
{
	if (vb_ptr == NULL) return;
	if (vb_ptr->scope_info != NULL)
	{
		free_scope_info(vb_ptr->scope_info);
		vb_ptr->scope_info = NULL;
	}
	if (vb_ptr->alias != NULL)
	{
		free_vector_string(vb_ptr->alias);
		vb_ptr->alias = NULL;
	}
	free_string(vb_ptr->type);
	free_string(vb_ptr->name);
	free_string(vb_ptr->value);
	destroy_variable_block(vb_ptr);
	vb_ptr = NULL;
}

void del_variable_block(void* a)
{
	variable_block* aa = (variable_block*)a;

	free_variable_block(aa);
}

int compare_variable_block(void* a, void* b)
{
	variable_block* aa = (variable_block*)a;
	variable_block* bb = (variable_block*)b;

	return compare_string(aa->name, bb->name);
}

void del_map_string_variable_block(void* key, void* value)
{
	//{string*, variable_block*}
	free_string((string*)key);
	free_variable_block((variable_block*)value);
}