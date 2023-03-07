#include "collections/list.h"
#include "collections/tree.h"
#include "collections/vector.h"
#include "collections/map.h"
#include "analysis/project_code.h"
#include "code/c/scanning_c.h"

// ±»Ωœ’˚–Œ
int compare_int(void* a, void* b)
{
	int aa = *(int*)a;
	int bb = *(int*)b;

	
	if (aa < bb) return -1;
	if (aa > bb) return 1;
	else return 0;
}

/* ≤‚ ‘»›∆˜
*  list, vector, map
*/
void test_collections()
{
	int a = 5, b = 7, c = 6, d = 8, e = 3;

	list* list_ptr = init_list();
	list_ptr->compare = compare_int;
	list_append_data(list_ptr, &a);
	list_append_data(list_ptr, &b);
	list_append_data(list_ptr, &c);

	free_list(list_ptr);


	int data[] = { 1,30,2,5,4,7,88,67,232 };

	binary_tree* tree_ptr = init_binary_tree();
	tree_ptr->compare = compare_int;
	int len = sizeof(data) / sizeof(data[0]);
	for (int i = 0; i < len; i++)
		binary_tree_add_data(tree_ptr, &data[i]);

	free_binary_tree(tree_ptr);

	vector* vector_ptr = init_vector();
	vector_ptr->compare = compare_int;
	vector_add_data(vector_ptr, &a);
	vector_add_data(vector_ptr, &b);
	vector_add_data(vector_ptr, &c);
	vector_remove_data(vector_ptr, &b);

	free_vector(vector_ptr);

	map* map_ptr = init_map();
	map_ptr->compare = compare_int;
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

// ≤‚ ‘¥˙¬Î±‡“Î∆˜
void test_code_complie(const char* root)
{
	lexical_analysis* la_ptr = init_lexical_analysis_c();

	project_code* pc_ptr = init_project_code();
	project_path_append_search_path(pc_ptr->proj_path, root);

	bool ret = project_code_load_entry_file(pc_ptr, "main.c");
}

int main(int argc, char** argv)
{
	if (argc > 0)
	{
		test_code_complie(argv[0]);
	}

	return 0;
}