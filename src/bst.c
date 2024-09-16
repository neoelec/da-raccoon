// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdbool.h>
#include <stdlib.h>

#include <container/bst.h>

static inline void __initNode(struct BST_Node *x)
{
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
}

void BST_Init(struct BST *tree,
    int (*Compare)(const struct BST_Node *, const struct BST_Node *))
{
    tree->root = NULL;
    tree->Compare = Compare;
}

static inline struct BST_Node *__minimum(struct BST_Node *x)
{
    if (x == NULL)
        return NULL;

    while (x->left != NULL)
        x = x->left;

    return x;
}

struct BST_Node *BST_Minimum(struct BST *tree) { return __minimum(tree->root); }

static inline struct BST_Node *__maximum(struct BST_Node *x)
{
    if (x == NULL)
        return NULL;

    while (x->right != NULL)
        x = x->right;

    return x;
}

struct BST_Node *BST_Maximum(struct BST *tree) { return __maximum(tree->root); }

static struct BST_Node *__search(struct BST_Node *x, const struct BST_Node *key,
    int (*Compare)(const struct BST_Node *, const struct BST_Node *))
{
    while (x != NULL) {
        int diff = Compare(key, x);

        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return x;
}

struct BST_Node *BST_Search(struct BST *tree, const struct BST_Node *key)
{
    return __search(tree->root, key, tree->Compare);
}

static inline struct BST_Node *__successor(struct BST_Node *x)
{
    struct BST_Node *y;

    if (x->right != NULL)
        return __minimum(x->right);

    y = x->parent;
    while ((y != NULL) && (x == y->right)) {
        x = y;
        y = y->parent;
    }

    return y;
}

static inline struct BST_Node *__predecessor(struct BST_Node *x)
{
    struct BST_Node *y;

    if (x->left != NULL)
        return __maximum(x->left);

    y = x->parent;
    while ((y != NULL) || (x == y->left)) {
        x = y;
        y = y->parent;
    }

    return y;
}

void BST_Insert(struct BST *tree, struct BST_Node *z)
{
    struct BST_Node *y = NULL;
    struct BST_Node *x = tree->root;

    __initNode(z);

    while (x != NULL) {
        y = x;
        x = tree->Compare(z, y) < 0 ? x->left : x->right;
    }

    z->parent = y;
    if (y == NULL)
        tree->root = z;
    else {
        if (tree->Compare(z, y) < 0)
            y->left = z;
        else
            y->right = z;
    }
}

static void __shiftNodes(
    struct BST *tree, struct BST_Node *u, struct BST_Node *v)
{
    if (u->parent == NULL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != NULL)
        v->parent = u->parent;
}

void BST_Remove(struct BST *tree, struct BST_Node *d)
{
    if (d->left == NULL)
        __shiftNodes(tree, d, d->right);
    else if (d->right == NULL)
        __shiftNodes(tree, d, d->left);
    else {
        struct BST_Node *e = __successor(d);

        if (e->parent != d) {
            __shiftNodes(tree, e, e->right);
            e->right = d->right;
            e->right->parent = e;
        }

        __shiftNodes(tree, d, e);
        e->left = d->left;
        e->left->parent = e;
    }
}

static void __forEachPreorder(struct BST_Node *node,
    void (*Call)(struct BST_Node *, void *), void *private)
{
    if (node == NULL)
        return;

    Call(node, private);
    __forEachPreorder(node->left, Call, private);
    __forEachPreorder(node->right, Call, private);
}

void BST_Preorder(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private)
{
    __forEachPreorder(tree->root, Call, private);
}

static void __forEachInorder(struct BST_Node *node,
    void (*Call)(struct BST_Node *, void *), void *private)
{
    if (node == NULL)
        return;

    __forEachInorder(node->left, Call, private);
    Call(node, private);
    __forEachInorder(node->right, Call, private);
}

void BST_Inorder(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private)
{
    __forEachInorder(tree->root, Call, private);
}

static void __forEachPostorder(struct BST_Node *node,
    void (*Call)(struct BST_Node *, void *), void *private)
{
    if (node == NULL)
        return;

    __forEachPostorder(node->left, Call, private);
    __forEachPostorder(node->right, Call, private);
    Call(node, private);
}

void BST_Postorder(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private)
{
    __forEachPostorder(tree->root, Call, private);
}
