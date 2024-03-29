#include "why_tree.h"
#include "why_tree_internal_decl.h"

void* tree_get_root(const Tree* tree)
{
    return tree->root;
}

int_signed tree_get_size(const Tree* tree)
{
    return tree->size;
}

void _linkL(Node* parent, Node* child)
{
    parent->left = child;

    if (child)
        child->parent = parent;
}

void _linkR(Node* parent, Node* child)
{
    parent->right = child;

    if (child)
        child->parent = parent;
}

static void* _create_linkL(Node* node, const void* item, void* (copy)(), void* (*node_constructor)())
{
    node->left = node_constructor(item, copy);
    node->left->parent = node;

    return node->left;
}

static void* _create_linkR(Node* node, const void* item, void* (copy)(), void* (*node_constructor)())
{
    node->right = node_constructor(item, copy);
    node->right->parent = node;

    return node->right;
}

static void _break_linkL(Node* node)
{
    if (!node->left)
        return ;
    
    node->left->parent = NULL;
    node->left = NULL;
}

static void _break_linkR(Node* node)
{
    if (!node->right)
        return ;
    
    node->right->parent = NULL;
    node->right = NULL;
}

void _break_link(Node* parent, Node* child)
{
    if (parent->left == child)
        _break_linkL(parent);
    else
        _break_linkR(parent);
}

void _reattach(Node* parent, Node* child, Node* new_child)
{
    if (parent->left == child)
    {
        _break_linkL(parent);
        _linkL(parent, new_child);
    }
    else
    {
        _break_linkR(parent);
        _linkR(parent, new_child);
    }
}

static Node* _find_root(Node* node)
{
    if (!node)
        return NULL;
    
    while (node->parent)
        node = node->parent;
    
    return node;
}

void* _insert(Node* root, const void* item, int_signed (*compare)(), void* (copy)())
{
    int_signed  result;
    Node*       new_node;
    
    if (!root)
        return NULL;

    result = compare(root->data, item);
    if (result > 0)
    {
        if (root->right)
            return _insert(root->right, item, compare, copy);
        
        new_node = _create_linkR(root, item, copy, _node_create);
    }
    else
    {
        if (root->left)
            return _insert(root->left, item, compare, copy);

        new_node = _create_linkL(root, item, copy, _node_create);
    }

    return new_node;
}

void* _insertAVL(AVLNode* node, const void* item, int_signed (*compare)(), void* (copy)())
{
    int_signed  result;
    AVLNode*    new_node;

    if (!node)
        return NULL;

    result = compare(node->data, item);
    if (result > 0)
    {
        if (node->right)
            return _insertAVL(node->right, item, compare, copy);
        
        new_node = _create_linkR((Node *)node, item, copy, _node_avl_create);
    }
    else if (result < 0)
    {
        if (node->left)
            return _insertAVL(node->left, item, compare, copy);
        
        new_node = _create_linkL((Node *)node, item, copy, _node_avl_create);
    }
    else return NULL;

    _balance(new_node);

    return new_node;
}

bool tree_insert(Tree* tree, const void* item)
{
    Node* node;

    if (!tree)
        return false;

    if (!tree->root)
    {
        tree->root = tree->node_create(item, tree->copy);
        tree->size = 1;

        return true;
    }
    
    if ((node = tree->node_insert(tree->root, item, tree->compare, tree->copy)))
    {
        tree->root = _find_root(tree->root);
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

int_signed _fold(const Node* node, int_signed (*function)())
{
    int_signed lhs;
    int_signed rhs;
    int_signed result;

    if (!node)
        return function(NULL);
    
    lhs = _fold(node->left, function);
    rhs = _fold(node->right, function);
    result = function(node) + lhs + rhs;

    return result; 
}

int_signed tree_fold(const Tree* tree, int_signed (*function)())
{
    if (!tree)
        return 0;
    
    return _fold(tree->root, function);
}

static Node* _find(const Node* node, const void* item, int_signed (*compare)())
{
    int_signed result;

    if (!node)
        return NULL;

    result = compare(node->data, item);
    if (result == 0)
        return (Node *)node;
    else if (result < 0)
        return _find(node->left, item, compare);
    else
        return _find(node->right, item, compare);
}

Node* _find_parent(Node* node, const void* item, int_signed (*compare)())
{
    Node* result;

    result = _find(node, item, compare);

    return result ? result->parent : NULL;
}

void* tree_find(const Tree* tree, const void* item)
{
    Node* result;

    if (!tree || !tree->root)
        return NULL;

    result = _find(tree->root, item, tree->compare);

    return result ? result->data : NULL;
}

static Node* _max(Node* node)
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

static Node* _min(Node* node)
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

static void* _remove_and_balance(Node* node, bool balance)
{
    Node* parent;
    Node* child;
    Node* min;

    parent = node->parent;
    if (_is_leaf(node))
        _break_link(parent, node);
    else if (_has_both_children(node))
    {
        min = _min(node->right);
        _swap(node, min);

        return _remove_and_balance(min, balance);
    }
    else if (node->left)
    {
        child = node->left;
        _reattach(parent, node, child);        
    }
    else
    {
        child = node->right;
        _reattach(parent, node, child);
    }

    if (balance)
        _balance((AVLNode *)parent);

    return node;
}

void* _remove(Node* node)
{
    return _remove_and_balance(node, false);
}

void* _removeAVL(Node* node)
{
    return _remove_and_balance(node, true);
}

static Node* _remove_root(Tree* tree)
{
    Node* node;
    Node* root;

    root = tree->root;
    if (_is_leaf(root))
    {
        node = root;
        tree->root = NULL;

        return node;
    }
    else if (_has_both_children(root))
    {
        node = _min(root->right);
        _swap(root, node);

        return _remove_and_balance(node, tree->avl);
    }
    else if (root->left)
    {
        _swap(root, root->left);
        return _remove_and_balance(root->left, tree->avl);
    }
    else
    {
        _swap(root, root->right);
        return _remove_and_balance(root->right, tree->avl);
    }
}

void* tree_remove(Tree* tree, const void* item)
{
    Node* node;
    void* data;

    if (!tree || !tree->size)
        return NULL;
    
    if (!(node = _find(tree->root, item, tree->compare)))
        return NULL;
    
    if (node == tree->root)
    {
        node = _remove_root(tree); 
        tree->root = _find_root(tree->root);
    }
    else
    {
        node = _remove_and_balance(node, tree->avl);
        tree->root = _find_root(tree->root);
    }
    
    data = node->data;
    _node_destroyNC(node);
    tree->size --;

    return data;
}

void* tree_pop_min(Tree* tree)
{
    Node* min;
    void* data;

    if (!tree || !tree->size)
        return NULL;

    if (tree->size == 1)
        min = _remove_root(tree);
    else if (((Node *)tree->root)->left == NULL)
        min = _remove_root(tree);
    else
    {
        min = _min(tree->root);
        min = _remove_and_balance(min, tree->avl);
        tree->root = _find_root(tree->root);
    }

    data = min->data;
    _node_destroyNC(min);
    tree->size --;

    return data;        
}

static int_signed _compute_height(const Node* node)
{
    int_signed lhs;
    int_signed rhs;

    if (!node)
        return -1;
    
    if (_is_leaf(node))
        return 0;
    
    lhs = _compute_height(node->left);
    rhs = _compute_height(node->right);

    return MAX(lhs, rhs) + 1;
}

int_signed tree_compute_height(const Tree* tree)
{
    if (!tree || !tree->root)
        return -1;
    
    return _compute_height(tree->root);
}