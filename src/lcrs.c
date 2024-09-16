// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/lcrs.h>

void LCRS_Init(struct LCRS *tree) { tree->root = NULL; }

void LCRS_InitNode(struct LCRS_Node *node)
{
    node->child = NULL;
    node->sibling = NULL;
}

void LCRS_Chain(struct LCRS_Node *parent, struct LCRS_Node *child)
{
    if (parent->child == NULL)
        parent->child = child;
    else {
        struct LCRS_Node *tmp = parent->child;
        while (tmp->sibling != NULL)
            tmp = tmp->sibling;

        tmp->sibling = child;
    }
}
