#include "why_tree_diagnostics.h"
#include "why_tree_internal_decl.h"

#include <assert.h>

void check_node_integrity(const Node* node)
{
    if (!node)
        return ;
    
    if (!node->parent)
        assert(0);
    
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