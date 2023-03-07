#include "path.h"
#include <io.h>
#include <process.h>

bool access_path(const char* path, int mode)
{
	if (path == NULL) return false;
#if WIN32
	int ret = _access(path, mode);
#else
	int ret = access(path, mode);
#endif // WIN32
	return ret == 0;
}

bool exists_path(const char* path)
{
	return access_path(path, 0);
}

bool can_write_path(const char* path)
{
	return access_path(path, 2);
}
bool can_read_path(const char* path)
{
	return access_path(path, 4);
}
bool can_operate_path(const char* path)
{
	return access_path(path, 8);
}

string* path_get_dir(const char* path)
{
	if (path == NULL) return NULL;

	string* fullpath = init_c_string(path);
	string* new_str = string_replace(fullpath, "\\", strlen("\\"), "/", strlen("/"));
	string* dir = NULL;
	int index = string_last_index(new_str, "/", strlen("/"));
	if (index != -1)
	{
		dir = sub_string(new_str, 0, index);
	}
	free_string(new_str);
	free_string(fullpath);

	return dir;
}

string* path_get_filename(const char* path)
{
	if (path == NULL) return NULL;

	string* fullpath = init_c_string(path);
	string* new_str = string_replace(fullpath, "\\", strlen("\\"), "/", strlen("/"));
	string* dir = NULL;
	int index = string_last_index(fullpath, "/", strlen("/"));
	if (index != -1)
	{
		dir = sub_string(new_str, index, fullpath->size - index);
	}
	free_string(new_str);
	free_string(fullpath);

	return dir;
}