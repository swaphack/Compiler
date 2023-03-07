#include "queue.h"
#include "macros.h"

CONSTRUCT_STRUCT(queue);

queue* init_queue()
{
	queue* que_ptr = create_queue();
	if (que_ptr == NULL) return NULL;
	que_ptr->capacity = COLLECTION_CAPACITY;
	void** temp = (void**)malloc(VOID_PTR_SIZE * que_ptr->capacity);
	if (temp != NULL)
	que_ptr->data = temp;
	que_ptr->front = 0;
	que_ptr->rear = 0;
	return que_ptr;
}

queue* init_queue_with_func(del_collection_data* del)
{
	queue* que_ptr = init_queue();
	if (que_ptr == NULL) return NULL;
	que_ptr->del = del;

	return que_ptr;
}

void queue_push_back(queue* que_ptr, void* data)
{
	if (que_ptr == NULL || data == NULL) return;

	if (que_ptr->rear + 1 >= que_ptr->capacity)
	{
		int count = 2 * que_ptr->capacity;
		void** temp = (void**)realloc(que_ptr->data, count * VOID_PTR_SIZE);
		if (temp == NULL)
		{
			return;
		}
		que_ptr->data = temp;
		que_ptr->capacity = count;
	}
	
	que_ptr->data[que_ptr->rear] = data;
	que_ptr->rear += 1;
}

void* queue_peek_front(queue* que_ptr)
{
	if (que_ptr == NULL) return NULL;
	if (que_ptr->front == que_ptr->rear) return NULL;

	if (que_ptr->front > COLLECTION_CAPACITY)
	{
		int len = que_ptr->rear - COLLECTION_CAPACITY;
		if (que_ptr->del != NULL)
		{
			for (int i = 0; i < COLLECTION_CAPACITY; i++)
			{
				if (que_ptr->data[i] != NULL)
				{
					que_ptr->del(que_ptr->data[i]);
				}
			}
		}
		
		memset(que_ptr->data, 0, COLLECTION_CAPACITY * VOID_PTR_SIZE);
		memmove(que_ptr->data, que_ptr->data + COLLECTION_CAPACITY, len * VOID_PTR_SIZE);

		que_ptr->front -= COLLECTION_CAPACITY;
		que_ptr->rear -= COLLECTION_CAPACITY;
	}

	void* data = que_ptr->data[que_ptr->front];
	que_ptr->front += 1;

	return data;
}
void* queue_back(queue* que_ptr)
{
	if (que_ptr == NULL) return NULL;
	if (que_ptr->front == que_ptr->rear) return NULL;
	if ((que_ptr->rear < que_ptr->front) || (que_ptr->rear == 0)) return NULL;
	return que_ptr->data[que_ptr->rear - 1];
}
void* queue_front(queue* que_ptr)
{
	if (que_ptr == NULL) return NULL;
	if (que_ptr->front == que_ptr->rear) return NULL;
	if ((que_ptr->rear < que_ptr->front)) return NULL;

	return que_ptr->data[que_ptr->front];
}
bool queue_empty(queue* que_ptr)
{
	if (que_ptr == NULL) return true;
	return que_ptr->front == que_ptr->rear;
}
void queue_clear(queue* que_ptr)
{
	if (que_ptr == NULL) return;
	if (que_ptr->del != NULL)
	{
		for (int i = 0; i < que_ptr->rear; i++)
		{
			if (que_ptr->data[i] != NULL)
			{
				que_ptr->del(que_ptr->data[i]);
			}
		}
		int len = que_ptr->capacity;
		memset(que_ptr->data + que_ptr->front, 0, len * VOID_PTR_SIZE);
		que_ptr->front = 0;
		que_ptr->rear = 0;
	}
}
void free_queue(queue* que_ptr)
{
	queue_clear(que_ptr);
	destroy_queue(que_ptr);
	que_ptr = NULL;
}