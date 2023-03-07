#include "project_code.h"
#include "data/macros.h"
#include "data/public_data.h"
#include "collections/extensions.h"
#include "stream/string_stream.h"
#include "lexical/scanning.h"
#include "lexical/lexical_analysis.h"
#include "analysis_table.h"
#include "block/struct_block.h"
#include "block/function_block.h"
#include <stdio.h>


#include "code/c/analysis_table_c.h"

CONSTRUCT_STRUCT(code_file_block);
CONSTRUCT_STRUCT(code_file);
CONSTRUCT_STRUCT(code_analysis_method);
CONSTRUCT_STRUCT(project_code);

code_file_block* init_code_file_block()
{
	code_file_block* cfb_ptr = create_code_file_block();
	if (cfb_ptr == NULL) return NULL;
	cfb_ptr->structs = init_map_with_string_key(del_map_string_struct_block);
	cfb_ptr->functions = init_map_with_string_key(del_map_string_function_block);
	return cfb_ptr;
}
void free_code_file_block(code_file_block* cfb_ptr)
{
	if (cfb_ptr == NULL) return;

	if (cfb_ptr->structs != NULL)
	{
		free_map(cfb_ptr->structs);
		cfb_ptr->structs = NULL;
	}

	if (cfb_ptr->functions != NULL)
	{
		free_map(cfb_ptr->functions);
		cfb_ptr->functions = NULL;
	}
	destroy_code_file_block(cfb_ptr);
	cfb_ptr = NULL;
}

code_file* init_code_file()
{
	code_file* cf_ptr = create_code_file();
	if (cf_ptr == NULL) return NULL;
	cf_ptr->include_files = init_vector();
	if (cf_ptr->include_files != NULL)
	{
		cf_ptr->include_files->del = del_string_key;
		cf_ptr->include_files->compare = compare_string_key;
	}

	cf_ptr->file_block = init_code_file_block();

	cf_ptr->tokens = init_string_list();

	return cf_ptr;
}
void free_code_file(code_file* cf_ptr)
{
	if (cf_ptr == NULL) return;

	free_string(cf_ptr->filepath);
	free_string(cf_ptr->text);
	free_code_file_block(cf_ptr->file_block);

	if (cf_ptr->include_files != NULL)
	{
		free_vector(cf_ptr->include_files);
		cf_ptr->include_files = NULL;
	}

	destroy_code_file(cf_ptr);
	cf_ptr = NULL;	
}

code_analysis_method* init_code_analysis_method()
{
	code_analysis_method* cam_ptr = create_code_analysis_method();
	if (cam_ptr == NULL) return NULL;
	cam_ptr->table = init_analysis_table();
	cam_ptr->scanning = init_lexical_analysis();
	if (cam_ptr->scanning != NULL)
	{
		cam_ptr->scanning->table_ptr = cam_ptr->table;
	}
	return cam_ptr;
}
void free_code_analysis_method(code_analysis_method* cam_ptr)
{
	if (cam_ptr == NULL)  return;
	if (cam_ptr->table != NULL)
	{
		free_analysis_table(cam_ptr->table);
		cam_ptr->table = NULL;
	}
	if (cam_ptr->scanning != NULL)
	{
		free_lexical_analysis(cam_ptr->scanning);
		cam_ptr->scanning = NULL;
	}
	destroy_code_analysis_method(cam_ptr);
	cam_ptr = NULL;
}

void del_map_string_code_file(void* key, void* value)
{
	free_string((string*)key);
	free_code_file((code_file*)value);
}

project_code* init_project_code()
{
	project_code* pc_ptr = create_project_code();
	if (pc_ptr == NULL) return NULL;
	pc_ptr->code_files = init_map_with_string_key(del_map_string_code_file);
	pc_ptr->proj_path = init_project_path();
	pc_ptr->analysis_method = init_code_analysis_method();
	pc_ptr->structs = init_string_map();
	return pc_ptr;
}

void free_project_code(project_code* pc_ptr)
{
	if (pc_ptr == NULL) return;

	free_string(pc_ptr->entry_file);
	if (pc_ptr->code_files != NULL)
	{
		free_map(pc_ptr->code_files);
		pc_ptr->code_files = NULL;
	}
	if (pc_ptr->proj_path != NULL)
	{
		free_project_path(pc_ptr->proj_path);
		pc_ptr->proj_path = NULL;
	}
	if (pc_ptr->analysis_method != NULL)
	{
		free_code_analysis_method(pc_ptr->analysis_method);
		pc_ptr->analysis_method = NULL;
	}
	
	destroy_project_code(pc_ptr);
	pc_ptr = NULL;
}

bool project_code_load_entry_file(project_code* pc_ptr, const char* filename)
{
	if (pc_ptr == NULL || filename == NULL) return false;

	pc_ptr->entry_file = init_c_string(filename);

	return project_code_load_file(pc_ptr, filename);
}

void scan_file_struct_block(void* a, void* b)
{
	struct_block* sb = (struct_block*)a;
	if (sb->name == NULL) return;

	project_code* pc_ptr = (project_code*)b;
	if (pc_ptr->data == NULL) return;
	string* filename = pc_ptr->data;

	map_add_data(pc_ptr->structs, clone_string(sb->name), clone_string(filename));
}

void scan_file_function_block(void* a, void* b)
{
	function_block* fb = (function_block*)a;
	if (fb->name == NULL) return;

	project_code* pc_ptr = (project_code*)b;
	if (pc_ptr->data == NULL) return;
	string* filename = pc_ptr->data;

	map_add_data(pc_ptr->functions, clone_string(fb->name), clone_string(filename));
}



bool project_code_load_file(project_code* pc_ptr, const char* filename)
{
	if (pc_ptr == NULL || filename == NULL) return false;

	string* fullpath = project_path_get_fullpath(pc_ptr->proj_path, filename);
	if (fullpath == NULL) return false;	

	string* text = project_path_get_text_with_fullpath(pc_ptr->proj_path, fullpath);
	code_file* cf_ptr = init_code_file();
	cf_ptr->filepath = fullpath;
	cf_ptr->text = text;

	code_analysis_method* analysis_method = pc_ptr->analysis_method;
	if (analysis_method != NULL)
	{
		if (analysis_method->scanning != NULL)
		{
			lexical_analysis_scan_code_file(analysis_method->scanning, cf_ptr);
		}
	}

	code_file_block* file_block = cf_ptr->file_block;
	if (file_block != NULL)
	{
		map_foreach_value(file_block->structs, scan_file_struct_block, cf_ptr);
		map_foreach_value(file_block->functions, scan_file_function_block, cf_ptr);
	}

	string* key = clone_string(fullpath);
	map_add_data(pc_ptr->code_files, key, cf_ptr);

	return true;
}

struct_block* project_code_get_struct_block(project_code* pc_ptr, const char* sb_name)
{
	if (pc_ptr == NULL || sb_name == NULL) return NULL;

	string* name = init_c_string(sb_name);
	string* filepath = (string*)map_get_value(pc_ptr->structs, name);
	if (filepath == NULL)
	{
		free_string(name);
		return NULL;
	}

	code_file* cf_ptr = (code_file*)map_get_value(pc_ptr->code_files, filepath);
	if (cf_ptr == NULL)
	{
		free_string(name);
		return NULL;
	}
	struct_block* sb_ptr = map_get_value(cf_ptr->file_block->structs, name);
	free_string(name);

	return sb_ptr;
}

function_block* project_code_get_function_block(project_code* pc_ptr, const char* fb_name)
{
	if (pc_ptr == NULL || fb_name == NULL) return NULL;

	string* name = init_c_string(fb_name);
	string* filepath = (string*)map_get_value(pc_ptr->functions, name);
	if (filepath == NULL)
	{
		free_string(name);
		return NULL;
	}

	code_file* cf_ptr = (code_file*)map_get_value(pc_ptr->code_files, filepath);
	if (cf_ptr == NULL)
	{
		free_string(name);
		return NULL;
	}
	function_block* fb_ptr = map_get_value(cf_ptr->file_block->functions, name);
	free_string(name);

	return fb_ptr;
}

void project_code_init_code_analysis_with(project_code* pc_ptr, code_type ct)
{
	if (pc_ptr == NULL) return;

	code_analysis_method* cam_method = pc_ptr->analysis_method;
	if (cam_method == NULL) return;

	analysis_table* at_ptr = cam_method->table;
	if (at_ptr == NULL) return;

	switch (ct)
	{
	case ect_c:
		init_analysis_table_with_c(at_ptr);
		break;
	default:
		break;
	}
}