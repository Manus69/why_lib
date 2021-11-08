#include "why_tree.h"
#include "why_tree_interface.h"
#include "why_tree_internal_decl.h"
#include "why_memory.h"
#include "why_macros.h"

#include <assert.h>

int_signed _node_get_height(const AVLNode* node)
{
    return node ? node->height : -1;
}

int_signed _node_get_balance(const AVLNode* node)
{
    if (!node)
        return 0;
    
    return _node_get_height(node->right) - _node_get_height(node->left);
}

void _update_height(AVLNode* node)
{
    int_signed lhs;
    int_signed rhs;
    
    if (!node)
        return ;

    lhs = _node_get_height(node->left);
    rhs = _node_get_height(node->right);
    node->height = MAX(lhs, rhs) + 1;

    return _update_height(node->parent);    
}

Node* _rotate_right(Node* node)
{
    Node* LR_subtree;
    Node* parent;
    Node* left;
    
    parent = node->parent;
    left = node->left;
    LR_subtree = node->left->right;

    _break_link(left, LR_subtree);
    _break_link(node, left);

    _linkL(node, LR_subtree);
    _linkR(left, node);
    
    if (parent)
        _reattach(parent, node, left);
    
    _update_height((AVLNode *)node);

    return left;
}

Node* _rotate_left(Node* node)
{
    Node* RL_subtree;
    Node* parent;
    Node* right;

    parent = node->parent;    
    right = node->right;
    RL_subtree = node->right->left;

    _break_link(node, right);
    _break_link(right, right->left);

    _linkR(node, RL_subtree);
    _linkL(right, node);

    if (parent)
        _reattach(parent, node, right);
    
    _update_height((AVLNode *)node);

    return right;
}

static AVLNode* _balance_lhs(AVLNode* node)
{
    if (_node_get_balance(node->left) > 0)
        return (AVLNode *)_rotate_right((Node *)node->left);
    
    return node;
}

static AVLNode* _balance_rhs(AVLNode* node)
{
    if (_node_get_balance(node->right) < 0)
        return (AVLNode *)_rotate_left((Node *)node->right);
    
    return node;
}

AVLNode* _check_balance_and_rotate(AVLNode* node)
{
    int_signed balance;

    balance = _node_get_balance(node);
    if (balance == -2)
    {
        _balance_lhs(node);
        return (AVLNode *)_rotate_right((Node *)node);
    }
    else if (balance == 2)
    {
        _balance_rhs(node);
        return (AVLNode *)_rotate_left((Node *)node);
    }
    
    return node;
}

static AVLNode* _find_violation(const AVLNode* node)
{
    if (!node)
        return NULL;
    
    if (ABS(_node_get_balance(node)) > 1)
        return (AVLNode *)node;
    
    return _find_violation(node->parent);
}

AVLNode* _balance(AVLNode* node)
{
    AVLNode* violation;

    if (!node)
        return NULL;
    
    _update_height(node);
    violation = _find_violation(node);

    return _check_balance_and_rotate(violation);
}
