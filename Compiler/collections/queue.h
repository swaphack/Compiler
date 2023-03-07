#pragma once

#include "data/macros.h"
#include "macros.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct queue
{
	void** data;
	// Ç°¶Ë
	int front;
	// ºó¶Ë
	int rear;
	// ÈÝÁ¿
	int capacity;
	// ÒÆ³ý
	del_collection_data* del;
}queue;

queue* init_queue();
queue* init_queue_with_func(del_collection_data* del);
void queue_push_back(queue* que_ptr, void* data);
void* queue_peek_front(queue* que_ptr);
void* queue_back(queue* que_ptr);
void* queue_front(queue* que_ptr);
bool queue_empty(queue* que_ptr);
void queue_clear(queue* que_ptr);
void free_queue(queue* que_ptr);


#ifdef __cplusplus
}
#endif