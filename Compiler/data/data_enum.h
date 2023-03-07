#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// 数据类型
typedef enum data_type
{
	edt_ptr,
	edt_int8,
	edt_uint8,
	edt_int16,
	edt_uint16,
	edt_int32,
	edt_uint32,
	edt_int64,
	edt_uint64,
	edt_float,
	edt_double,
	edt_string,
}data_type;

#ifdef __cplusplus
}
#endif