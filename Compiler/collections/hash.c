#include "hash.h"
#include "data/data.h"

CONSTRUCT_STRUCT(hash_table);
CONSTRUCT_STRUCT(hash_node);

uint64_t get_hash_code(const char* key)
{
    uint64_t h = 0;
    while (*key)
    {
        h = (h << 4) + *key++;
        uint64_t g = h & 0xF0000000L;
        if (g)
            h ^= g >> 24;
        h &= ~g;
    }
    return h;
}

void free_hash_node(hash_node* node)
{
    if (node == NULL) return;
    if (node->name != NULL)
    {
        free_string(node->name);
    }
    free(node);
}

int compare_list_node(void* a, void* b)
{
    hash_node* aa = (hash_node*)a;
    uint64_t ha = aa->hash;
    uint64_t hb = get_hash_code(b);
    if (ha < hb) return -1;
    if (ha > hb) return 1;
    return strcmp(aa->name->value, (char*)b);
}

hash_table* init_hash_table()
{
    hash_table* hash_ptr = create_hash_table();
    return hash_ptr;
}

void hash_table_resize(hash_table* hash_ptr, int mod)
{
    if (hash_ptr == NULL) return;
    if (mod <= 1) return;

    if (hash_ptr->mod > 1)
    {
        for (int i = 0; i < hash_ptr->mod; i++)
        {
            free_list(hash_ptr->list[i]);
        }
        hash_ptr->list = NULL;
        hash_ptr->mod = 0;
    }

    int size = mod * sizeof(list*);
    hash_ptr->list = (list**)malloc(size);
    if (hash_ptr->list == NULL) return;
    hash_ptr->mod = mod;
    memset(hash_ptr->list, 0, size);
    for (int i = 0; i < mod; i++)
    {
        list* list = init_list();
        list->compare = compare_list_node;
        list->del = free_hash_node;
        hash_ptr->list[i] = list;
    }
}
bool hash_table_contains_data(hash_table* hash_ptr, const char* name)
{
    if (hash_ptr == NULL || hash_ptr->mod <= 0) return false;
    if (name == NULL) return false;

    uint64_t hash_code = get_hash_code(name);
    int index = hash_code % hash_ptr->mod;
    if (index < 0 || index >= hash_ptr->mod) return false;
    return list_contains_data(hash_ptr->list[index], (void*)name);
}
void hash_table_add_data(hash_table* hash_ptr, const char* name, void* data)
{
    if (hash_ptr == NULL || hash_ptr->mod <= 0) return;
    if (name == NULL) return;

    uint64_t hash_code = get_hash_code(name);
    int index = hash_code % hash_ptr->mod;
    if (index < 0 || index >= hash_ptr->mod) return;
    hash_node* node = create_hash_node();
    node->hash = hash_code;
    node->name = init_c_string(name);
    node->data = data;
    list_append_data(hash_ptr->list[index], (void*)name);
}
void hash_table_remove_data(hash_table* hash_ptr, const char* name)
{
    if (hash_ptr == NULL || hash_ptr->mod <= 0) return;
    if (name == NULL) return;

    uint64_t hash_code = get_hash_code(name);
    int index = hash_code % hash_ptr->mod;
    if (index < 0 || index >= hash_ptr->mod) return;

    list_remove_data(hash_ptr->list[index], (void*)name);
}

void hash_table_clear(hash_table* hash_ptr)
{
    if (hash_ptr == NULL || hash_ptr->mod <= 0) return;

    for (int i = 0; i < hash_ptr->mod; i++)
    {
        list_clear(hash_ptr->list[i]);
    }
}

void free_hash_table(hash_table* hash_ptr)
{
    if (hash_ptr == NULL) return;
    if (hash_ptr->mod > 1)
    {
        for (int i = 0; i < hash_ptr->mod; i++)
        {
            free_list(hash_ptr->list[i]);
        }
        free(hash_ptr->list);
        hash_ptr->list = NULL;
        hash_ptr->mod = 0;
    }

    destroy_hash_table(hash_ptr);
}
