
#ifndef WHY_LIST_INTERFACE_H
#define WHY_LIST_INTERFACE_H

#include "why_definitions.h"

typedef struct Sequence Sequence;
typedef struct List List;

#ifdef __cplusplus
    extern "C" {
#endif

List*   list_create(void* (*copy)(), void (*_destroy)());
void    list_destroy(List* list);
List*   list_push_back(List* list, const void* data);
List*   list_push_front(List* list, const void* data);
void*   list_pop_back(List* list);
void*   list_pop_front(List* list);
List*   list_reverse(List* list);
void    list_map(List* list, void (*function)());

#ifdef __cplusplus
    }
#endif

#endif
