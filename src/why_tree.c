#include "why_tree.h"
#include "why_tree_interface.h"
#include "why_tree_internal_decl.h"
#include "why_memory.h"
#include "why_macros.h"

void* _node_create(const void* data, void* (*copy)())
{
    Node* node;

    node = allocate(sizeof(Node));
    node->data = copy(data);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

void* _node_avl_create(const void* data, void* (*copy)())
{
    AVLNode* node;

    node = allocate(sizeof(AVLNode));
    node->data = copy(data);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 0;

    return node;
}

void _node_destroy(Node* node, void (*destroy)())
{
    destroy(node->data);
    free(node);
}

void _node_destroyNC(Node* node)
{
    free(node);
}

Tree* tree_create(void* (*copy)(), void (*destroy)(), int_signed (*compare)())
{
    Tree* tree;

    tree = allocate(sizeof(Tree));
    tree->copy = copy;
    tree->destroy = destroy;
    tree->compare = compare;

    tree->root = NULL;
    tree->size = 0;
    tree->avl = false;

    tree->node_create = _node_create;
    tree->node_insert = _insert;

    return tree;
}

void _convert_to_avl(Tree* tree)
{
    tree->avl = true;
    tree->node_create = _node_avl_create;
    tree->node_insert = _insertAVL;
}

Tree* tree_create_avl(void* (*copy)(), void (*destroy)(), int_signed (*compare)())
{
    Tree* tree;

    tree = tree_create(copy, destroy, compare);
    _convert_to_avl(tree);

    return tree;
}

void _destroy_nodes(Node* root, void (*destroy)())
{
    Node* left;
    Node* right;
    
    if (!root)
        return ;

    left = root->left;
    right = root->right;

    if (destroy)
        _node_destroy(root, destroy);
    else
        _node_destroyNC(root);
    
    _destroy_nodes(left, destroy);
    _destroy_nodes(right, destroy);
}

void tree_destroy(Tree* tree)
{
    if (!tree)
        return ;
    
    _destroy_nodes(tree->root, tree->destroy);
    free(tree);
}
