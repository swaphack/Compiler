#pragma once

#include "data/macros.h"
#include "data/string_data.h"

#ifdef __cplusplus
extern "C" {
#endif

bool access_path(const char* path, int mode);
bool exists_path(const char* path);
bool can_write_path(const char* path);
bool can_read_path(const char* path);
bool can_operate_path(const char* path);

string* path_get_dir(const char* path);
string* path_get_filename(const char* path);


#ifdef __cplusplus
}
#endif