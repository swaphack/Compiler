#include "collections/list.h"
#include "collections/binary_tree.h"
#include "collections/vector.h"
#include "collections/map.h"
#include "analysis/project_code.h"
#include "code/c/scanning_c.h"
#include "project/path.h"
#include "regex/regex.h"
#include <stdio.h>

int compare_int_ptr(void* a, void* b)
{
	int aa = *(int*)a;
	int bb = *(int*)b;

	
	if (aa < bb) return -1;
	if (aa > bb) return 1;
	else return 0;
}

void test_collections()
{
	int a = 5, b = 7, c = 6, d = 8, e = 3;

	list* list_ptr = init_list();
	list_ptr->compare = compare_int_ptr;
	list_append_data(list_ptr, &a);
	list_append_data(list_ptr, &b);
	list_append_data(list_ptr, &c);

	free_list(list_ptr);


	int data[] = { 1,30,2,5,4,7,88,67,232 };

	binary_tree* tree_ptr = init_binary_tree();
	tree_ptr->compare = compare_int_ptr;
	int len = sizeof(data) / sizeof(data[0]);
	for (int i = 0; i < len; i++)
		binary_tree_add_data(tree_ptr, &data[i]);

	free_binary_tree(tree_ptr);

	vector* vector_ptr = init_vector();
	vector_ptr->compare = compare_int_ptr;
	vector_add_data(vector_ptr, &a);
	vector_add_data(vector_ptr, &b);
	vector_add_data(vector_ptr, &c);
	vector_remove_data(vector_ptr, &b);

	free_vector(vector_ptr);

	map* map_ptr = init_map();
	map_ptr->compare = compare_int_ptr;
	map_add_data(map_ptr, &a, &b);
	map_add_data(map_ptr, &b, &c);
	map_add_data(map_ptr, &c, &d);
	map_add_data(map_ptr, &d, &e);
	map_add_data(map_ptr, &e, &a);

	void* t = map_get_value(map_ptr, &c);
	if (t != NULL)
	{
		int value = *(int*)t;
		int sdf = 0;
	}

	map_remove_data(map_ptr, &b);

	t = map_get_value(map_ptr, &b);
	if (t != NULL)
	{
		int value = *(int*)t;
	}

	t = map_get_value(map_ptr, &c);
	if (t != NULL)
	{
		int value = *(int*)t;
	}

	t = map_get_value(map_ptr, &d);
	if (t != NULL)
	{
		int value = *(int*)t;
	}
	t = map_get_value(map_ptr, &e);
	if (t != NULL)
	{
		int value = *(int*)t;
	}

	free_map(map_ptr);
}

void test_code_complie(const char* root)
{
	project_code* pc_ptr = init_project_code();
	project_code_init_code_analysis_with(pc_ptr, ect_c);

	string* fullpath = path_get_dir(root);
	project_path_append_search_path(pc_ptr->proj_path, fullpath->value);
	free_string(fullpath);

	bool ret = project_code_load_entry_file(pc_ptr, "main.c");


	free_project_code(pc_ptr);
}

#define X_ADD_1 (x + 1)

int x = 2;

void d()
{
	printf("d=>%d\n", X_ADD_1);
}

void b()
{
	int x = 1; 
	printf("b=>%d\n", X_ADD_1);
	d();
}

void c()
{
	printf("c=>%d\n", X_ADD_1);
}


void test_regex()
{
	regex* reg = init_regex();
	const char* pattern1 = "(<a\\s*(?!.*\\brel=)[^>]*)(href=\"https ? : \\ / \\ / )((? !(? : (? : www\\.) ? '.implode(' | (? : www\\.) ? ', $follow_list).'))[^ \" rel=\"external nofollow\" ]+)\"((? !.*\\brel = )[^ > ] *)(? : [^ > ] *) >";
	const char* pattern2 = "[\u4e00 - \u9fa5]";
	const char* pattern3 = "^([a-zA-Z]+-?)+[a-zA-Z0-9]+\.[x|X][m|M][l|L]$";
	const char* pattern4 = "(<a\\s*(?!.*\\brel=)[^>]*)";

	const char* pattern5 = "[0-9]+\\.[0-9]+";
	const char* string1 = "3.1415926";

	int ret = regex_comp(reg, pattern3, 0);
	if (ret == 0)
	{
		size_t nmatch = 10;
		regmatch* pmatch = (regmatch*)malloc(sizeof(regmatch) * nmatch);
		ret = regex_exec(reg, string1, nmatch, pmatch, 0);
	}
	free_regex(reg);
}

int main(int argc, char** argv)
{
	//if (argc > 0) test_code_complie(argv[0]);

	test_regex();

	return 0;
}