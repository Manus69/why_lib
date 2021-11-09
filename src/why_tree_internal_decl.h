#ifndef WHY_TREE_INTERNAL_DECL_H
#define WHY_TREE_INTERNAL_DECL_H

#include "why_tree.h"

int_signed  _node_get_balance(const AVLNode* node);
int_signed  _node_get_height(const AVLNode* node);
bool        _balance_is_invalid(const AVLNode* node);
void        _linkL(Node* parent, Node* child);
void        _linkR(Node* parent, Node* child);
void        _break_link(Node* parent, Node* child);
void        _reattach(Node* parent, Node* child, Node* new_child);
void*       _insert(Node* root, const void* item, int_signed (*compare)(), void* (*copy)());
void*       _insertAVL(AVLNode* node, const void* item, int_signed (*compare)(), void* (*copy)());
void*       _node_create(const void* data, void* (*copy)());
void*       _node_avl_create(const void* data, void* (*copy)());
void        _node_destroy(Node* node, void (*destroy)());
void        _node_destroyNC(Node* node);
void        _convert_to_avl(Tree* tree);
void        _destroy_nodes(Node* root, void (*destroy)());
AVLNode*    _check_balance_and_rotate(AVLNode* node);
void        _update_height(AVLNode* node);
AVLNode*    _balance(AVLNode* node);

#endif