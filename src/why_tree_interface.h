
#ifndef WHY_TREE_INTERFACE_H
#define WHY_TREE_INTERFACE_H

#include "why_definitions.h"

typedef struct Tree Tree;

#ifdef __cplusplus
    extern "C" {
#endif

Tree*       tree_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)());
void*       tree_get_root(const Tree* tree);
int_signed  tree_get_size(const Tree* tree);
bool        tree_insert(Tree* tree, const void* item);
void*       tree_remove(Tree* tree, const void* item);
void*       tree_find(Tree* tree, const void* item);
void        tree_map_inorder(Tree* tree, void (*function)());

#ifdef __cplusplus
    }
#endif

#endif
