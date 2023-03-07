#pragma once

#include "macros.h"
#include "data_enum.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct base_data
{
	void* value;
	int size;
	enum data_type type;

} base_data;

base_data* create_data(void* value, int size);
base_data* create_int8_data(int8_t value);
base_data* create_uint8_data(uint8_t value);
base_data* create_int16_data(int16_t value);
base_data* create_uint16_data(uint16_t value);
base_data* create_int32_data(int32_t value);
base_data* create_uint32_data(uint32_t value);
base_data* create_int64_data(int64_t value);
base_data* create_uint64_data(uint64_t value);
base_data* create_float_data(float value);
base_data* create_double_data(double value);
base_data* create_string_data(char* value);
void free_data(base_data* data);

int8_t as_int8(base_data* data);
uint8_t as_uint8(base_data* data);
int16_t as_int16(base_data* data);
uint16_t as_uint16(base_data* data);
int32_t as_int32(base_data* data);
uint32_t as_uint32(base_data* data);
int64_t as_int64(base_data* data);
uint64_t as_uint64(base_data* data);
float as_float(base_data* data);
double as_double(base_data* data);

// ±È½Ï
int compare_int(int a, int b);

#ifdef __cplusplus
}
#endif