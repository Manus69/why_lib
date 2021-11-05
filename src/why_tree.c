#include "why_tree.h"
#include "why_tree_interface.h"
#include "why_memory.h"

static void* _node_create(const void* data)
{
    Node* node;

    node = allocate(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

static void* _node_avl_create(const void* data)
{
    AVLNode* node;

    node = allocate(sizeof(AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->height = 0;
    node->balance = 0;

    return node;
}

static void _node_destroy(Node* node, void (*destroy)())
{
    destroy(node->data);
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

    tree->create = _node_create;
    tree->insert = _insert;

    return tree;
}

void* tree_get_root(const Tree* tree);
int_signed tree_get_size(const Tree* tree);

static void _linkL(AVLNode* parent, AVLNode* child)
{
    parent->left = child;
    child->parent = parent;
}

static void _linkR(AVLNode* parent, AVLNode* child)
{
    parent->right = child;
    child->parent = parent;
}

static void _create_linkL(AVLNode* node, const void* item)
{
    node->left = _node_avl_create(item);
    node->left->parent = node;
}

static void _create_linkR(AVLNode* node, const void* item)
{
    node->right = _node_avl_create(item);
    node->right->parent = node;
}

static bool _insert(Node* root, const void* item, int_signed (*compare)())
{
    int_signed result;
    
    if (!root)
        return false;

    result = compare(root->data, item);
    if (result > 0)
    {
        if (root->right)
            return _insert(root->right, item, compare);
        
        root->right = _node_create(item);
    }
    else
    {
        if (root->left)
            return _insert(root->left, item, compare);

        root->left = _node_create(item);
    }

    return true;
}

static bool _insertAVL(AVLNode* node, const void* item, int_signed (*compare)())
{
    int_signed result;

    if (!node)
        return false;

    result = compare(node->data, item);
    if (result > 0)
    {
        if (node->right)
            return _insertAVL(node->right, item, compare);
        
        _create_linkR(node, item);
    }
    else if (result < 0)
    {
        if (node->left)
            return _insertAVL(node->left, item, compare);
        
        _create_linkL(node, item);
    }
    else return false;
    
    return true;
}

bool tree_insert(Tree* tree, const void* item)
{
    if (!tree)
        return false;

    if (!tree->root)
    {
        tree->root = tree->create(item);
        tree->size = 1;
    }
    
    if (tree->insert(tree->root, item, tree->compare))
    {
        tree->size ++;
        return true;
    }

    return false;
}

static void _map_inorder(Node* node, void (*function)())
{
    if (!node)
        return ;
    
    _map_inorder(node->left, function);
    function(node->data);
    _map_inorder(node->right, function);
}

void tree_map_inorder(Tree* tree, void (*function)())
{
    if (!tree)
        return ;

    _map_inorder(tree->root, function);
}

void* tree_remove(Tree* tree, const void* item);
void* tree_find(Tree* tree, const void* item);