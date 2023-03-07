#include "stack.h"
#include "macros.h"

CONSTRUCT_STRUCT(stack)

stack* init_stack()
{
	stack* stack_ptr = create_stack();
	if (stack_ptr == NULL) return NULL;
	stack_ptr->capacity = COLLECTION_CAPACITY;
	void** temp = (void**)malloc(VOID_PTR_SIZE * stack_ptr->capacity);
	if (temp != NULL)
		stack_ptr->data = temp;
	stack_ptr->size = 0;
	return stack_ptr;
}

stack* init_stack_with_func(del_collection_data* del)
{
	stack* stack_ptr = init_stack();
	if (stack_ptr == NULL) return NULL;
	stack_ptr->del = del;
	return stack_ptr;
}

void stack_push(stack* stack_ptr, void* data)
{
	if (stack_ptr == NULL || data == NULL) return;

	if (stack_ptr->size + 1 >= stack_ptr->capacity)
	{
		int count = 2 * stack_ptr->capacity;
		void** temp = (void**)realloc(stack_ptr->data, count * VOID_PTR_SIZE);
		if (temp == NULL)
		{
			return;
		}
		stack_ptr->data = temp;
		stack_ptr->capacity = count;
	}
	stack_ptr->data[stack_ptr->size] = data;
	stack_ptr->size += 1;
}

void stack_pop(stack* stack_ptr)
{
	if (stack_ptr == NULL) return;
	if (stack_ptr->size == 0) return;

	void* data = stack_ptr->data[stack_ptr->size - 1];
	if (stack_ptr->del != NULL)
	{
		stack_ptr->del(data);
	}
	stack_ptr->data[stack_ptr->size - 1] = NULL;
	stack_ptr->size -= 1;
}

void* stack_top(stack* stack_ptr)
{
	if (stack_ptr == NULL) return NULL;
	if (stack_ptr->size == 0) return NULL;

	return stack_ptr->data[stack_ptr->size - 1];
}

bool stack_empty(stack* stack_ptr)
{
	if (stack_ptr == NULL) return true;
	return stack_ptr->size == 0;
}

void stack_clear(stack* stack_ptr)
{
	if (stack_ptr == NULL) return;

	if (stack_ptr->del != NULL)
	{
		for (int i = 0; i < stack_ptr->size; i++)
		{
			stack_ptr->del(stack_ptr->data[i]);
		}
	}
	memset(stack_ptr->data, 0, stack_ptr->size * VOID_PTR_SIZE);
	stack_ptr->size = 0;
}
void free_stack(stack* stack_ptr)
{
	if (stack_ptr == NULL) return;

	stack_clear(stack_ptr);
	if (stack_ptr->capacity > 0)
	{
		free(stack_ptr->data);
		stack_ptr->data = NULL;
		stack_ptr->size = 0;
		stack_ptr->capacity = 0;
	}

	destroy_stack(stack_ptr);
	stack_ptr = NULL;
}