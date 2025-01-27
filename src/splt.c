// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/splt.h>

#define __compare(tree, a, b) (tree)->Compare(a, b)

void SPLT_Init(struct SPLT *tree, int (*Compare)(const struct SPLT_Node *,
                                                 const struct SPLT_Node *))
{
    tree->root = NULL;
    tree->Compare = Compare;
}

static inline bool __isEmpty(const struct SPLT *tree)
{
    return (tree->root == NULL) ? true : false;
}

bool SPLT_IsEmpty(const struct SPLT *tree)
{
    return __isEmpty(tree);
}

static inline struct SPLT_Node *__minimum(const struct SPLT *tree,
                                          const struct SPLT_Node *x)
{
    while (x->left != NULL)
        x = x->left;

    return (struct SPLT_Node *)x;
}

struct SPLT_Node *SPLT_Minimum(const struct SPLT *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __minimum(tree, tree->root);
}

static inline struct SPLT_Node *__maximum(const struct SPLT *tree,
                                          const struct SPLT_Node *x)
{
    while (x->right != NULL)
        x = x->right;

    return (struct SPLT_Node *)x;
}

struct SPLT_Node *SPLT_Maximum(const struct SPLT *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __maximum(tree, tree->root);
}

static inline struct SPLT_Node *__search(const struct SPLT *tree,
                                         const struct SPLT_Node *x,
                                         const struct SPLT_Node *k)
{
    while (x != NULL) {
        int diff = __compare(tree, k, x);
        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return (struct SPLT_Node *)x;
}

struct SPLT_Node *SPLT_Search(const struct SPLT *tree,
                              const struct SPLT_Node *k)
{
    struct SPLT_Node *x = __search(tree, tree->root, k);

    return x == NULL ? NULL : x;
}

static inline void __rotateLeft(struct SPLT *tree, struct SPLT_Node *x)
{
    struct SPLT_Node *y;

    y = x->right;
    if (y) {
        x->right = y->left;
        if (y->left)
            y->left->parent = x;

        y->parent = x->parent;
    }

    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    if (y)
        y->left = x;

    x->parent = y;
}

static inline void __rotateRight(struct SPLT *tree, struct SPLT_Node *x)
{
    struct SPLT_Node *y;

    y = x->left;
    if (y) {
        x->left = y->right;
        if (y->right)
            y->right->parent = x;

        y->parent = x->parent;
    }

    if (x->parent == NULL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    if (y)
        y->right = x;

    x->parent = y;
}

static inline void __splay(struct SPLT *tree, struct SPLT_Node *x)
{
    while (x->parent) {
        if (!x->parent->parent) {
            if (x->parent->left == x)
                __rotateRight(tree, x->parent);
            else
                __rotateLeft(tree, x->parent);
        } else if (x->parent->left == x &&
                   x->parent->parent->left == x->parent) {
            __rotateRight(tree, x->parent->parent);
            __rotateRight(tree, x->parent);
        } else if (x->parent->right == x &&
                   x->parent->parent->right == x->parent) {
            __rotateLeft(tree, x->parent->parent);
            __rotateLeft(tree, x->parent);
        } else if (x->parent->left == x &&
                   x->parent->parent->right == x->parent) {
            __rotateRight(tree, x->parent);
            __rotateLeft(tree, x->parent);
        } else {
            __rotateLeft(tree, x->parent);
            __rotateRight(tree, x->parent);
        }
    }
}

static inline void __insert(struct SPLT *tree, struct SPLT_Node *z)
{
    struct SPLT_Node *y;
    struct SPLT_Node *x;

    x = tree->root;
    y = NULL;

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

    __splay(tree, z);
}

void SPLT_Insert(struct SPLT *tree, struct SPLT_Node *z)
{
    __insert(tree, z);

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static inline void __transplant(struct SPLT *tree, struct SPLT_Node *u,
                                struct SPLT_Node *v)
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

static inline void __remove(struct SPLT *tree, struct SPLT_Node *z)
{
    struct SPLT_Node *y;

    __splay(tree, z);

    if (!z->left)
        __transplant(tree, z, z->right);
    else if (!z->right)
        __transplant(tree, z, z->left);
    else {
        y = __minimum(tree, z->right);
        if (y->parent != z) {
            __transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        __transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

void SPLT_Remove(struct SPLT *tree, struct SPLT_Node *z)
{
    __remove(tree, z);

    z->parent = z;

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static inline struct SPLT_Node *__next(const struct SPLT *tree,
                                       struct SPLT_Node *x)
{
    struct SPLT_Node *parent;

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

static inline struct SPLT_Node *__prev(const struct SPLT *tree,
                                       struct SPLT_Node *x)
{
    struct SPLT_Node *parent;

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

void SPLT_Forward(struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *),
                  void *private)
{
    struct SPLT_Node *x = __minimum(tree, tree->root);

    while (x != NULL) {
        Call(x, private);
        x = __next(tree, x);
    }
}

void SPLT_Backward(struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *),
                   void *private)
{
    struct SPLT_Node *x = __maximum(tree, tree->root);

    while (x != NULL) {
        Call(x, private);
        x = __prev(tree, x);
    }
}

static void __forEachPreorder(const struct SPLT *tree, struct SPLT_Node *x,
                              void (*Call)(struct SPLT_Node *, void *),
                              void *private)
{
    if (x == NULL)
        return;

    Call(x, private);
    __forEachPreorder(tree, x->left, Call, private);
    __forEachPreorder(tree, x->right, Call, private);
}

void SPLT_Preorder(struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *),
                   void *private)
{
    __forEachPreorder(tree, tree->root, Call, private);
}

static void __forEachInorder(const struct SPLT *tree, struct SPLT_Node *x,
                             void (*Call)(struct SPLT_Node *, void *),
                             void *private)
{
    if (x == NULL)
        return;

    __forEachInorder(tree, x->left, Call, private);
    Call(x, private);
    __forEachInorder(tree, x->right, Call, private);
}

void SPLT_Inorder(struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *),
                  void *private)
{
    __forEachInorder(tree, tree->root, Call, private);
}

static void __forEachPostorder(const struct SPLT *tree, struct SPLT_Node *x,
                               void (*Call)(struct SPLT_Node *, void *),
                               void *private)
{
    if (x == NULL)
        return;

    __forEachPostorder(tree, x->left, Call, private);
    __forEachPostorder(tree, x->right, Call, private);
    Call(x, private);
}

void SPLT_Postorder(struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *),
                    void *private)
{
    __forEachPostorder(tree, tree->root, Call, private);
}
