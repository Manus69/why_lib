#include "why_tree.h"
#include "why_tree_interface.h"
#include "why_memory.h"
#include "why_macros.h"

static bool _insert(Node* root, const void* item, int_signed (*compare)(), void* (*copy)());
static bool _insertAVL(AVLNode* node, const void* item, int_signed (*compare)(), void* (*copy)());

static void* _node_create(const void* data, void* (*copy)())
{
    Node* node;

    node = allocate(sizeof(Node));
    node->data = copy(data);
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;

    return node;
}

static void* _node_avl_create(const void* data, void* (*copy)())
{
    AVLNode* node;

    node = allocate(sizeof(AVLNode));
    node->data = copy(data);
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

    tree->node_create = _node_create;
    tree->node_insert = _insert;

    return tree;
}

static void _convert_to_avl(Tree* tree)
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

static void _destroy_nodes(Node* root, void (*destroy)())
{
    Node* left;
    Node* right;
    
    if (!root)
        return ;

    left = root->left;
    right = root->right;

    _node_destroy(root, destroy);
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

void* tree_get_root(const Tree* tree)
{
    return tree->root;
}

int_signed tree_get_size(const Tree* tree)
{
    return tree->size;
}

static void _linkL(Node* parent, Node* child)
{
    parent->left = child;
    child->parent = parent;
}

static void _linkR(Node* parent, Node* child)
{
    parent->right = child;
    child->parent = parent;
}

static void _create_linkL(Node* node, const void* item, void* (copy)())
{
    node->left = _node_avl_create(item, copy);
    node->left->parent = node;
}

static void _create_linkR(Node* node, const void* item, void* (copy)())
{
    node->right = _node_avl_create(item, copy);
    node->right->parent = node;
}

static void _break_linkL(Node* node)
{
    node->left->parent = NULL;
    node->left = NULL;
}

static void _break_linkR(Node* node)
{
    node->right->parent = NULL;
    node->right = NULL;
}

static bool _insert(Node* root, const void* item, int_signed (*compare)(), void* (copy)())
{
    int_signed result;
    
    if (!root)
        return false;

    result = compare(root->data, item);
    if (result > 0)
    {
        if (root->right)
            return _insert(root->right, item, compare, copy);
        
        _create_linkR(root, item, copy);
    }
    else
    {
        if (root->left)
            return _insert(root->left, item, compare, copy);

        _create_linkL(root, item, copy);
    }

    return true;
}

static bool _insertAVL(AVLNode* node, const void* item, int_signed (*compare)(), void* (copy)())
{
    int_signed result;

    if (!node)
        return false;

    result = compare(node->data, item);
    if (result > 0)
    {
        if (node->right)
            return _insertAVL(node->right, item, compare, copy);
        
        _create_linkR((Node *)node, item, copy);
    }
    else if (result < 0)
    {
        if (node->left)
            return _insertAVL(node->left, item, compare, copy);
        
        _create_linkL((Node *)node, item, copy);
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
        tree->root = tree->node_create(item, tree->copy);
        tree->size = 1;

        return true;
    }
    
    if (tree->node_insert(tree->root, item, tree->compare, tree->copy))
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

static Node* _find(Node* node, const void* item, int_signed (*compare)())
{
    int_signed result;

    if (!node)
        return NULL;

    result = compare(node->data, item);
    if (result == 0)
        return node;
    else if (result < 0)
        return _find(node->left, item, compare);
    else
        return _find(node->right, item, compare);
}

static Node* _find_parent(Node* node, const void* item, int_signed (*compare)())
{
    Node* result;

    result = _find(node, item, compare);

    return result ? result->parent : NULL;
}

void* tree_find(Tree* tree, const void* item)
{
    Node* result;

    if (!tree || !tree->root)
        return NULL;

    result = _find(tree->root, item, tree->compare);

    return result ? result->data : NULL;
}

static Node* _max(const Node* node)
{
    while (node->right)
        node = node->right;
    
    return node;
}

void* tree_max(Tree* tree)
{
    if (!tree || !tree->size)
        return NULL;

    return _max(tree->root)->data;
}

static Node* _min(const Node* node)
{
    while (node->left)
        node = node->left;
    
    return node;
}

void* tree_min(Tree* tree)
{
    if (!tree || !tree->size)
        return NULL;
    
    return _min(tree->root)->data;
}

static bool _is_leaf(const Node* node)
{
    return !node->left && !node->right;
}

static bool _has_both_children(const Node* node)
{
    return node->left && node->right;
}

static void _swap(Node* lhs, Node* rhs)
{
    SWAP(lhs->data, rhs->data, void *);
}

static Node* _remove(Node* node, const void* item, int_signed (*compare)())
{
    Node* parent;
    Node* result;

    result = _find(node, item, compare);
    parent = result->parent;
}

void* tree_remove(Tree* tree, const void* item)
{
    ;
}