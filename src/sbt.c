// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/sbt.h>

void SBT_Init(struct SBT *tree) { tree->root = NULL; }

void SBT_InitNode(struct SBT_Node *node)
{
    node->left = NULL;
    node->right = NULL;
}

static void __forEachPreorder(struct SBT_Node *node,
    void (*Call)(struct SBT_Node *, void *), void *private)
{
    if (node == NULL)
        return;

    Call(node, private);
    __forEachPreorder(node->left, Call, private);
    __forEachPreorder(node->right, Call, private);
}

void SBT_Preorder(
    struct SBT *tree, void (*Call)(struct SBT_Node *, void *), void *private)
{
    __forEachPreorder(tree->root, Call, private);
}

static void __forEachInorder(struct SBT_Node *node,
    void (*Call)(struct SBT_Node *, void *), void *private)
{
    if (node == NULL)
        return;

    __forEachInorder(node->left, Call, private);
    Call(node, private);
    __forEachInorder(node->right, Call, private);
}

void SBT_Inorder(
    struct SBT *tree, void (*Call)(struct SBT_Node *, void *), void *private)
{
    __forEachInorder(tree->root, Call, private);
}

static void __forEachPostorder(struct SBT_Node *node,
    void (*Call)(struct SBT_Node *, void *), void *private)
{
    if (node == NULL)
        return;

    __forEachPostorder(node->left, Call, private);
    __forEachPostorder(node->right, Call, private);
    Call(node, private);
}

void SBT_Postorder(
    struct SBT *tree, void (*Call)(struct SBT_Node *, void *), void *private)
{
    __forEachPostorder(tree->root, Call, private);
}
