#include "scope_info.h"
#include "data/data.h"


CONSTRUCT_STRUCT(scope_info);

scope_info* init_scope_info()
{
	scope_info* si_ptr = create_scope_info();
	return si_ptr;
}

void scope_info_init_with(scope_info* si_ptr, scope_type type, void* scope)
{
	if (si_ptr == NULL) return;

	si_ptr->type = type;
	si_ptr->scope = scope;
}

void free_scope_info(scope_info* si_ptr)
{
	if (si_ptr == NULL) return;
	destroy_scope_info(si_ptr);
	si_ptr = NULL;
}