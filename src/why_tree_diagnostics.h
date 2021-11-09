#ifndef WHY_TREE_DIAGNOSTICS_H
#define WHY_TREE_DIAGNOSTICS_H

#include "why_tree.h"

void tree_check_integrity(const Tree* tree);
void tree_check_avl_invariant(const Tree* tree);

#endif