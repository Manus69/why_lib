#include "why_tree_diagnostics.h"
#include "why_tree_internal_decl.h"

#include <assert.h>

void check_node_integrity(const Node* node)
{
    if (!node)
        return ;
    
    assert(node->parent);
    
    check_node_integrity(node->left);
    check_node_integrity(node->right);
}

void check_root_integrity(const Node* root)
{
    check_node_integrity(root->left);
    check_node_integrity(root->right);
}

void tree_check_integrity(const Tree* tree)
{
    if (!tree || !tree->root)
        assert(0);

    check_root_integrity(tree->root);
}

void check_avl_node_invariant(const AVLNode* node)
{
    if (!node)
        return ;
    
    if (_balance_is_invalid(node))
        assert(0);
    
    check_avl_node_invariant(node->left);
    check_avl_node_invariant(node->right);
}

void tree_check_avl_invariant(const Tree* tree)
{
    if (!tree || !tree->root)
        assert(0);
    
    check_avl_node_invariant(tree->root);
}

static int_signed _id(const Node* node)
{
    return node ? 1 : 0;
}

void tree_check_size(const Tree* tree)
{
    int_signed size;

    size = _fold(tree->root, _id);
    assert(tree->size == size);
}

void _check_search_invariant(const Node* node, int_signed (*compare)())
{
    int_signed result;

    if (!node)
        return ;

    if (node->left && node->right)
    {
        result = compare(node->left->data, node->right->data);
        assert(result > 0);
        result = compare(node->left->data, node->data);
        assert(result > 0);
        result = compare(node->right->data, node->data);
        assert(result < 0);
    }
    else if (node->left)
    {
        result = compare(node->left->data, node->data);
        assert(result > 0);
    }
    else if (node->right)
    {
        result = compare(node->right->data, node->data);
        assert(result < 0);
    }

    _check_search_invariant(node->left, compare);
    _check_search_invariant(node->right, compare);
}

void tree_check_search_invariant(const Tree* tree)
{
    if (!tree || !tree->root)
        return ;
    
    _check_search_invariant(tree->root, tree->compare);
}