#include "why_tree.h"
#include "why_tree_interface.h"
#include "why_memory.h"

Node* _rotate_right(Node* node)
{
    Node* LL_subtree;
    Node* LR_subtree;
    Node* R_subtree;
    Node* parent;
    Node* left;

    if ((parent = node->parent))
        _break_link(parent, node);
    
    left = node->left;
    LL_subtree = node->left->left;
    LR_subtree = node->left->right;
    R_subtree = node->right;

    _break_link(node->left, LR_subtree);
    _break_link(node, node->left);

    _reattach(node, left, LR_subtree);
    _reattach(left, LR_subtree, node);

    if (parent)
        _reattach(parent, node, left);
    
    return left;
}

void tree_testRR(Tree* tree)
{
    ;
}