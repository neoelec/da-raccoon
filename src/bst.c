// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdbool.h>
#include <stdlib.h>

#include <container/bst.h>

#define __compare(tree, a, b) (tree)->Compare(a, b)

void BST_Init(struct BST *tree,
    int (*Compare)(const struct BST_Node *, const struct BST_Node *))
{
    tree->root = NULL;
    tree->Compare = Compare;
}

static inline bool __isEmpty(const struct BST *tree)
{
    return (tree->root == NULL) ? true : false;
}

bool BST_IsEmpty(const struct BST *tree) { return __isEmpty(tree); }

static inline struct BST_Node *__minimum(const struct BST_Node *x)
{
    while (x->left != NULL)
        x = x->left;

    return (struct BST_Node *)x;
}

struct BST_Node *BST_Minimum(const struct BST *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __minimum(tree->root);
}

static inline struct BST_Node *__maximum(const struct BST_Node *x)
{
    while (x->right != NULL)
        x = x->right;

    return (struct BST_Node *)x;
}

struct BST_Node *BST_Maximum(const struct BST *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __maximum(tree->root);
}

static struct BST_Node *__search(
    const struct BST *tree, struct BST_Node *x, const struct BST_Node *k)
{
    while (x != NULL) {
        int diff = __compare(tree, k, x);
        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return x;
}

struct BST_Node *BST_Search(
    const struct BST *tree, const struct BST_Node *k)
{
    return __search(tree, tree->root, k);
}

static inline void __insert(struct BST *tree, struct BST_Node *z)
{
    struct BST_Node *y;
    struct BST_Node *x;

    y = NULL;
    x = tree->root;

    while (x != NULL) {
        y = x;
        x = __compare(tree, z, x) < 0 ? x->left : x->right;
    }

    z->parent = y;

    if (y == NULL)
        tree->root = z;
    else if (__compare(tree, z, y) < 0)
        y->left = z;
    else
        y->right = z;

    z->left = NULL;
    z->right = NULL;
}

void BST_Insert(struct BST *tree, struct BST_Node *z)
{
    __insert(tree, z);

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static void __transplant(
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

static inline void __remove(struct BST *tree, struct BST_Node *z)
{
    if (z->left == NULL)
        __transplant(tree, z, z->right);
    else if (z->right == NULL)
        __transplant(tree, z, z->left);
    else {
        struct BST_Node *y = __minimum(z->right);

        if (y != z->right) {
            __transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        __transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void BST_Remove(struct BST *tree, struct BST_Node *z)
{
    __remove(tree, z);

    z->parent = z;

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static inline struct BST_Node *__next(
    const struct BST *tree, struct BST_Node *x)
{
    struct BST_Node *parent;

    if (x->right != NULL) {
        x = x->right;
        while (x->left != NULL)
            x = x->left;

        return x;
    }

    parent = x->parent;
    while ((parent != NULL) && (x == parent->right)) {
        x = parent;
        parent = x->parent;
    }

    return parent;
}

static inline struct BST_Node *__prev(
    const struct BST *tree, struct BST_Node *x)
{
    struct BST_Node *parent;

    if (x->left != NULL) {
        x = x->left;
        while (x->right != NULL)
            x = x->right;

        return x;
    }

    parent = x->parent;
    while ((parent != NULL) && (x == parent->left)) {
        x = parent;
        parent = x->parent;
    }

    return parent;
}

void BST_Forward(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private)
{
    struct BST_Node *x = __minimum(tree->root);

    while (x != NULL) {
        Call(x, private);
        x = __next(tree, x);
    }
}

void BST_Backward(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private)
{
    struct BST_Node *x = __maximum(tree->root);

    while (x != NULL) {
        Call(x, private);
        x = __prev(tree, x);
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
