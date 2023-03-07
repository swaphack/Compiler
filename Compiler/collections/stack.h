#pragma once

#include "data/macros.h"
#include "macros.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct stack
{
	void** data;
	// ÊýÁ¿
	int size;
	// ÈÝÁ¿
	int capacity;
	// ÒÆ³ý
	del_collection_data* del;
}stack;

stack* init_stack();
stack* init_stack_with_func(del_collection_data* del);
void stack_push(stack* stack_ptr, void* data);
void stack_pop(stack* stack_ptr);
void* stack_top(stack* stack_ptr);
bool stack_empty(stack* stack_ptr);
void stack_clear(stack* stack_ptr);
void free_stack(stack* stack_ptr);

#ifdef __cplusplus
}
#endif