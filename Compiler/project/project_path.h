#pragma once

#include "data/macros.h"
#include "collections/list.h"
#include "collections/map.h"
#include "data/string_data.h"

#ifdef __cplusplus
extern "C" {
#endif

// 工程路径
typedef struct project_path
{
	// 搜索路径 {string*}
	list* search_paths;
	// 已搜索路径 {string*, string*}
	map* searched_filepaths;

}project_path;

project_path* init_project_path();
void project_path_append_search_path(project_path* pp_ptr, const char* path);
void project_path_remove_search_path(project_path* pp_ptr, const char* path);
void project_path_remove_all_search_paths(project_path* pp_ptr);
bool project_path_exists_path(project_path* pp_ptr, const char* filepath);

void project_path_remove_all_searched_paths(project_path* pp_ptr);
string* project_path_get_fullpath(project_path* pp_ptr, const char* filename);
string* project_path_get_text_with_filename(project_path* pp_ptr, const char* filename);
string* project_path_get_text_with_fullpath(project_path* pp_ptr, string* fullpath);
void free_project_path(project_path* pp_ptr);

#ifdef __cplusplus
}
#endif