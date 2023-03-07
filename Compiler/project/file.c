#include "file.h"

CONSTRUCT_STRUCT(file_info);

file_info* init_file_info(const char* path)
{
	file_info* fi_ptr = create_file_info();
	if (path != NULL)
	{
		fi_ptr->filepath = init_c_string(path);
	}
	return fi_ptr;
}

FILE* open_file(const char* path, const char* mode)
{
	if (path == NULL || mode == NULL) return NULL;
#if WIN32
	FILE* fptr = NULL;
	errno_t tid = fopen_s(&fptr, path, mode);
	if (tid != 0) return NULL;
#else
	FILE* fptr = fopen(fi_ptr->filepath->value, mode);
	if (fptr == NULL) return NULL;
#endif // WIN32	
	return fptr;
}

string* file_read(file_info* fi_ptr)
{
	if (fi_ptr == NULL) return NULL;
	if (fi_ptr->filepath == NULL) return NULL;

	FILE* fptr = open_file(fi_ptr->filepath->value, "rb+");
	if (fptr == NULL) return NULL;

	fseek(fptr, 0, SEEK_END);
	size_t count = ftell(fptr);
	char* data = (char*)malloc(sizeof(char) * count);
	if (data == NULL)
	{
		fclose(fptr);
		return NULL;
	}
	fseek(fptr, 0, SEEK_SET);
	size_t len = fread(data, sizeof(char), count, fptr);
	if (len < 0)
	{
		free(data); 
		fclose(fptr);
		return NULL;
	}

	string* text = init_string(data, len);
	free(data);
	fclose(fptr);

	return text;

}
void file_write(file_info* fi_ptr, string* text)
{
	if (fi_ptr == NULL) return;
	if (fi_ptr->filepath == NULL) return;

	FILE* fptr = open_file(fi_ptr->filepath->value, "wb+");
	if (fptr == NULL) return;
	fwrite(text->value, sizeof(char), text->size, fptr);
	fclose(fptr);
}

void file_append(file_info* fi_ptr, string* text)
{
	if (fi_ptr == NULL || text == NULL) return;
	if (fi_ptr->filepath == NULL) return;

	FILE* fptr = open_file(fi_ptr->filepath->value, "ab+");
	if (fptr == NULL) return;
	fwrite(text->value, sizeof(char), text->size, fptr);
	fclose(fptr);
}

void file_save(file_info* fi_ptr, string* text)
{
	if (fi_ptr == NULL) return;
	if (fi_ptr->filepath == NULL || text == NULL) return;

	FILE* fptr = open_file(fi_ptr->filepath->value, "wb+");
	if (fptr == NULL) return;
	fwrite(text->value, sizeof(char), text->size, fptr);
	fclose(fptr);
}

void free_file_info(file_info* fi_ptr)
{
	if (fi_ptr == NULL) return;
	free_string(fi_ptr->filepath);
	fi_ptr->filepath = NULL;
	destroy_file_info(fi_ptr);
	fi_ptr = NULL;
}

string* file_get_text(string* fullpath)
{
	if (fullpath == NULL) return NULL;
	file_info* fi_ptr = init_file_info(fullpath->value);
	if (fi_ptr == NULL)
	{
		return NULL;
	}
	string* text = file_read(fi_ptr);
	free_file_info(fi_ptr);
	return text;
}