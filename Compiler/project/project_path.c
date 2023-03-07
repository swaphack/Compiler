#include "project_path.h"
#include "path.h"
#include "file.h"
#include "collections/extensions.h"

CONSTRUCT_STRUCT(project_path)

project_path* init_project_path()
{
	project_path* pp_ptr = create_project_path();
	if (pp_ptr == NULL) return NULL;
	pp_ptr->search_paths = init_string_list();
	pp_ptr->searched_filepaths = init_string_map();
	return pp_ptr;
}
void project_path_append_search_path(project_path* pp_ptr, const char* path)
{
	if (pp_ptr == NULL || path == NULL) return;
	if (pp_ptr->search_paths == NULL) return;

	string* str = init_c_string(path);
	if (!string_ends_with(str, "/", 1))
		string_append_char(str, 1, '/');
	list_append_data(pp_ptr->search_paths, str);
}
void project_path_remove_search_path(project_path* pp_ptr, const char* path)
{
	if (pp_ptr == NULL || path == NULL) return;
	if (pp_ptr->search_paths == NULL) return;

	string* str = init_c_string(path);
	list_remove_data(pp_ptr->search_paths, str);
	free_string(str);
}
void project_path_remove_all_search_paths(project_path* pp_ptr)
{
	if (pp_ptr == NULL) return;
	if (pp_ptr->search_paths == NULL) return;

	list_clear(pp_ptr->search_paths);
}
bool project_path_exists_path(project_path* pp_ptr, const char* filepath)
{
	if (pp_ptr == NULL || filepath == NULL) return false;
	if (pp_ptr->search_paths == NULL) return false;

	list_node* node = pp_ptr->search_paths->root;
	while (node != NULL)
	{
		string* temp = (string*)node->data;
		string* fullpath = append_c_str(temp, filepath, strlen(filepath));
		if (fullpath == NULL) continue;
		bool ret = exists_path(fullpath->value);
		free_string(fullpath);
		if (ret) return true;
		node = node->next;
	}

	return false;
}

void project_path_remove_all_searched_paths(project_path* pp_ptr)
{
	if (pp_ptr == NULL) return;
	if (pp_ptr->searched_filepaths == NULL) return;

	map_clear(pp_ptr->searched_filepaths);
}

string* project_path_get_fullpath(project_path* pp_ptr, const char* filename)
{
	if (pp_ptr == NULL || filename == NULL) return NULL;
	if (pp_ptr->search_paths == NULL || pp_ptr->searched_filepaths == NULL) return NULL;

	string* str_filename = init_c_string(filename);

	map_value* value = map_get_value(pp_ptr->searched_filepaths, str_filename);
	if (value != NULL)
	{
		free_string(str_filename);
		return (string*)value->value;
	}

	string* fullpath = NULL;
	list_node* node = pp_ptr->search_paths->root;
	while (node != NULL)
	{
		string* path = (string*)node->data;
		string* temp = append_c_str(path, filename, strlen(filename));
		if (temp == NULL) continue;
		bool ret = exists_path(temp->value);
		if (ret)
		{
			fullpath = temp;
			break;
		}
		free_string(temp);
		node = node->next;
	}

	
	map_add_data(pp_ptr->searched_filepaths, str_filename, clone_string(fullpath));

	return fullpath;
}

string* project_path_get_text_with_filename(project_path* pp_ptr, const char* filename)
{
	if (pp_ptr == NULL || filename == NULL) return NULL;

	string* fullpath = project_path_get_fullpath(pp_ptr, filename);
	if (fullpath == NULL) return NULL;

	string* text = project_path_get_text_with_fullpath(pp_ptr, fullpath);
	free_string(fullpath);

	return text;
}

string* project_path_get_text_with_fullpath(project_path* pp_ptr, string* fullpath)
{
	if (pp_ptr == NULL || fullpath == NULL) return NULL;

	string* text = file_get_text(fullpath);

	return text;
}

void free_project_path(project_path* pp_ptr)
{
	if (pp_ptr == NULL) return;

	if (pp_ptr->search_paths != NULL)
	{
		free_list(pp_ptr->search_paths);
		pp_ptr->search_paths = NULL;
	}
	if (pp_ptr->searched_filepaths != NULL)
	{
		free_map(pp_ptr->searched_filepaths);
		pp_ptr->searched_filepaths = NULL;
	}
	destroy_project_path(pp_ptr);
	pp_ptr = NULL;
}