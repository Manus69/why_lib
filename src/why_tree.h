#ifdef __cplusplus
    extern "C" {
#endif

#ifndef WHY_TREE_H
#define WHY_TREE_H

#include "why_tree_interface.h"

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
    int_signed  balance;
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
    bool        (*node_insert)();
};


#endif

#ifdef __cplusplus
    }
#endif