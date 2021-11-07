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

void    _linkL(Node* parent, Node* child);
void    _linkR(Node* parent, Node* child);
void    _break_link(Node* parent, Node* child);
void    _reattach(Node* parent, Node* child, Node* new_child);
bool    _insert(Node* root, const void* item, int_signed (*compare)(), void* (*copy)());
bool    _insertAVL(AVLNode* node, const void* item, int_signed (*compare)(), void* (*copy)());
void*   _node_create(const void* data, void* (*copy)());
void*   _node_avl_create(const void* data, void* (*copy)());
void    _node_destroy(Node* node, void (*destroy)());
void    _node_destroyNC(Node* node);
void    _convert_to_avl(Tree* tree);
void    _destroy_nodes(Node* root, void (*destroy)());
Node*   _rotate_right(Node* node);

#endif
