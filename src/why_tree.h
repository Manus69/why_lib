#ifndef WHY_TREE_H
#define WHY_TREE_H

#include "why_definitions.h"

typedef struct Node Node;
typedef struct AVLNode AVLNode;

struct Node
{
    void*       data;
    Node*       left;
    Node*       right;
    Node*       parent;
};

struct AVLNode
{
    void*       data;
    AVLNode*    left;
    AVLNode*    right;
    AVLNode*    parent;
    int_signed  height;
};

struct Tree
{
    void*       root;
    void*       (*copy)();
    void        (*destroy)();
    int_signed  (*compare)();
    int_signed  size;
    bool        avl;

    void*       (*node_create)();
    void*       (*node_insert)();
    // void*       (*node_remove)();
};

#endif
