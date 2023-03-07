#include "data.h"
#include "string.h"

CONSTRUCT_STRUCT(base_data);

#define INIT_DATA_VALUE(data, T, value)\
data->size = sizeof(T);\
data->value = (T*)malloc(data->size);\
if (data->value != NULL) \
	memcpy(data->value, &value, data->size);\

base_data* create_data(void* value, int size)
{
	base_data* data = create_base_data();
	data->size = size;
	data->value = (void*)malloc(data->size); 
	if (data->value != NULL) 
		memcpy(data->value, &value, data->size); 
	data->type = edt_ptr;
	return data;
}

base_data* create_int8_data(int8_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, int8_t, value);
	data->type = edt_int8;
	return data;
}

base_data* create_uint8_data(uint8_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, uint8_t, value);
	data->type = edt_uint8;
	return data;
}

base_data* create_int16_data(int16_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, int16_t, value);
	data->type = edt_int16;
	return data;
}

base_data* create_uint16_data(uint16_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, uint16_t, value);
	data->type = edt_uint16;
	return data;
}

base_data* create_int32_data(int32_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, int32_t, value);
	data->type = edt_int32;
	return data;
}

base_data* create_uint32_data(uint32_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, uint32_t, value);
	data->type = edt_uint32;
	return data;
}

base_data* create_int64_data(int64_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, int64_t, value);
	data->type = edt_int64;
	return data;
}

base_data* create_uint64_data(uint64_t value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, uint64_t, value);
	data->type = edt_uint64;
	return data;
}

base_data* create_float_data(float value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, float, value);
	data->type = edt_float;
	return data;
}

base_data* create_double_data(double value)
{
	base_data* data = create_base_data();
	INIT_DATA_VALUE(data, double, value);
	data->type = edt_double;
	return data;
}

base_data* create_string_data(char* value)
{
	base_data* data = create_base_data();
	data->size = strlen(value); 
	data->value = (char*)malloc(data->size);
	if (data->value != NULL)
		memcpy(data->value, &value, data->size); 
	data->type = edt_string;
	return data;
}

void free_data(base_data* data)
{
	if (data == NULL) return;
	if (data->value != NULL)
	{
		free(data->value);
		data->value = NULL;
	}
	destroy_base_data(data);
}

#define GET_DATA_VALUE(data, T, E)\
if (data == NULL || data->size == 0 || data->value == NULL) return 0;\
if (data->type != E) return 0;\
T* ptr = data->value;\
return *(ptr); 


int8_t as_int8(base_data* data)
{
	GET_DATA_VALUE(data, int8_t, edt_int8);
}
uint8_t as_uint8(base_data* data)
{
	GET_DATA_VALUE(data, uint8_t, edt_uint8);
}
int16_t as_int16(base_data* data)
{
	GET_DATA_VALUE(data, int16_t, edt_int16);
}
uint16_t as_uint16(base_data* data)
{
	GET_DATA_VALUE(data, uint16_t, edt_uint16);
}
int32_t as_int32(base_data* data)
{
	GET_DATA_VALUE(data, int32_t, edt_int32);
}
uint32_t as_uint32(base_data* data)
{
	GET_DATA_VALUE(data, uint32_t, edt_uint32);
}
int64_t as_int64(base_data* data)
{
	GET_DATA_VALUE(data, int64_t, edt_int64);
}
uint64_t as_uint64(base_data* data)
{
	GET_DATA_VALUE(data, uint64_t, edt_uint64);
}
float as_float(base_data* data)
{
	GET_DATA_VALUE(data, float, edt_float);
}
double as_double(base_data* data)
{
	GET_DATA_VALUE(data, double, edt_double);
}

int compare_int(int a, int b)
{
	if (a < b) return -1;
	if (a > b) return 1;
	else return 0;
}