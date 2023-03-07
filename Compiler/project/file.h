#pragma once

#include "data/string_data.h"
#include "data/macros.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct file_info
{
	string* filepath;
}file_info;

file_info* init_file_info(const char* path);
FILE* open_file(const char* path, const char* mode);
string* file_read(file_info* fi_ptr);
void file_write(file_info* fi_ptr, string* text);
void file_append(file_info* fi_ptr, string* text);
void file_save(file_info* fi_ptr, string* text);
void free_file_info(file_info* fi_ptr);
// 获取文件内容
string* file_get_text(string* fullpath);

#ifdef __cplusplus
}
#endif