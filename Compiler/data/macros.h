#pragma once
#include <stdlib.h>
#include <string.h>

#ifndef _STDBOOL_H 
#define _STDBOOL_H 

#ifndef __cplusplus 

#define bool    _Bool 
#define true    1 
#define false   0 

#else /* __cplusplus */ 

/* Supporting <stdbool.h> in C++ is a GCC extension.  */
#define _Bool   bool 
#define bool    bool 
#define false   false 
#define true    true 

#endif /* __cplusplus */ 

#endif

#ifdef __cplusplus
extern "C"{
#endif


#define CREATE_STRUCT(T)\
T* create_##T()\
{\
T* data = (T*)malloc(sizeof(T));\
if (data == NULL) return NULL;\
memset(data, 0, sizeof(T));\
return data;\
}

#define DESTROY_STRUCT(T)\
void destroy_##T(T* data)\
{\
if (data == NULL) return;\
free(data);\
data = NULL;\
}

#define CONSTRUCT_STRUCT(T)\
T* create_##T()\
{\
T* data = (T*)malloc(sizeof(T));\
if (data == NULL) return NULL;\
memset(data, 0, sizeof(T));\
return data;\
}\
void destroy_##T(T* data)\
{\
if (data == NULL) return;\
free(data);\
data = NULL;\
}


#define REMOVE_NODE_DATA(C, N) \
void remove_##N##_data(C* ptr, N* node)\
{ \
	if (ptr == NULL || node == NULL) return; \
	if (ptr->del != NULL) ptr->del(node->data); \
}

#ifdef __cplusplus
}
#endif