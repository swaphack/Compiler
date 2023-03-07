#pragma once

#include "collections/stack.h"
#include "data/data.h"
#include "op_codes.h"

#ifdef __cplusplus
extern "C" {
#endif

// ²Ù×÷ÃüÁî
typedef struct op_command
{
	op_codes code;
	base_data* data;

}op_unit;

// ²Ù×÷¶ÑÕ»
typedef struct op_stack
{
	stack* stack;
}op_stack;

op_stack* init_op_stack();
void op_stack_emit(op_stack* stack, op_codes code, base_data* data);
void op_stack_emit_call(op_stack* stack, op_codes code, base_data* data);

#ifdef __cplusplus
}
#endif