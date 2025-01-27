// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/avl.h>

#include "common.h"

#define __compare(tree, a, b) (tree)->Compare(a, b)

void AVL_Init(struct AVL *tree,
              int (*Compare)(const struct AVL_Node *, const struct AVL_Node *))
{
    tree->root = NULL;
    tree->Compare = Compare;
}

static inline bool __isEmpty(const struct AVL *tree)
{
    return (tree->root == NULL) ? true : false;
}

bool AVL_IsEmpty(const struct AVL *tree)
{
    return __isEmpty(tree);
}

static inline struct AVL_Node *__minimum(const struct AVL_Node *x)
{
    while (x->left != NULL)
        x = x->left;

    return (struct AVL_Node *)x;
}

struct AVL_Node *AVL_Minimum(const struct AVL *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __minimum(tree->root);
}

static inline struct AVL_Node *__maximum(const struct AVL_Node *x)
{
    while (x->right != NULL)
        x = x->right;

    return (struct AVL_Node *)x;
}

struct AVL_Node *AVL_Maximum(const struct AVL *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __maximum(tree->root);
}

static inline struct AVL_Node *__search(const struct AVL *tree,
                                        const struct AVL_Node *x,
                                        const struct AVL_Node *k)
{
    while (x != NULL) {
        int diff = __compare(tree, k, x);
        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return (struct AVL_Node *)x;
}

struct AVL_Node *AVL_Search(const struct AVL *tree, const struct AVL_Node *k)
{
    return __search(tree, tree->root, k);
}

static inline void __setLeftChild(struct AVL_Node *x, struct AVL_Node *c)
{
    x->left = c;

    if (c != NULL)
        c->parent = x;
}

static inline void __setRightChild(struct AVL_Node *x, struct AVL_Node *c)
{
    x->right = c;

    if (c != NULL)
        c->parent = x;
}

static inline ssize_t __height(struct AVL_Node *x)
{
    return x ? x->height : 0;
}

static inline struct AVL_Node *__rotateLeft(struct AVL_Node *x)
{
    struct AVL_Node *y = x->right;
    struct AVL_Node *t2 = y->left;

    __setLeftChild(y, x);
    __setRightChild(x, t2);

    x->height = MAX(__height(x->left), __height(x->right)) + 1;
    y->height = MAX(__height(y->left), __height(y->right)) + 1;

    return y;
}

static inline struct AVL_Node *__rotateRight(struct AVL_Node *y)
{
    struct AVL_Node *x = y->left;
    struct AVL_Node *t2 = x->right;

    __setRightChild(x, y);
    __setLeftChild(y, t2);

    y->height = MAX(__height(y->left), __height(y->right)) + 1;
    x->height = MAX(__height(x->left), __height(x->right)) + 1;

    return x;
}

static inline ssize_t __balanceFactor(struct AVL_Node *x)
{
    return x ? __height(x->left) - __height(x->right) : 0;
}

static struct AVL_Node *
__rebalanceInsertion(struct AVL *tree, struct AVL_Node *x, struct AVL_Node *z)
{
    ssize_t bf;

    x->height = MAX(__height(x->left), __height(x->right)) + 1;

    bf = __balanceFactor(x);
    if (bf > 1 && __compare(tree, z, x->left) < 0) { // left left case
        return __rotateRight(x);
    } else if (bf < -1 &&
               __compare(tree, z, x->right) > 0) { // right right case
        return __rotateLeft(x);
    } else if (bf > 1 && __compare(tree, z, x->left) > 0) { // left right case
        __setLeftChild(x, __rotateLeft(x->left));
        return __rotateRight(x);
    } else if (bf < -1 && __compare(tree, z, x->right) < 0) { // right left case
        __setRightChild(x, __rotateRight(x->right));
        return __rotateLeft(x);
    }

    return x;
}

static struct AVL_Node *__insert(struct AVL *tree, struct AVL_Node *x,
                                 struct AVL_Node *z)
{
    if (x == NULL)
        return z;
    else if (__compare(tree, z, x) < 0)
        __setLeftChild(x, __insert(tree, x->left, z));
    else if (__compare(tree, z, x) > 0)
        __setRightChild(x, __insert(tree, x->right, z));
    else
        return x;

    return __rebalanceInsertion(tree, x, z);
}

void AVL_Insert(struct AVL *tree, struct AVL_Node *z)
{
    z->left = NULL;
    z->right = NULL;
    z->height = 0;

    tree->root = __insert(tree, tree->root, z);

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static inline struct AVL_Node *__exchange(const struct AVL_Node *a,
                                          struct AVL_Node *b)
{
    __setLeftChild(b, a->left);
    __setRightChild(b, a->right);

    b->height = a->height;
    b->parent = a->parent;

    if (a->parent == NULL)
        return b;
    else if (a->parent->left == a)
        a->parent->left = b;
    else
        a->parent->right = b;

    return b;
}

static struct AVL_Node *__rebalanceRemoval(struct AVL *tree, struct AVL_Node *x)
{
    ssize_t bf;

    if (x == NULL)
        return NULL;

    x->height = MAX(__height(x->left), __height(x->right)) + 1;

    bf = __balanceFactor(x);
    if (bf > 1 && __balanceFactor(x->left) >= 0) {
        return __rotateRight(x);
    } else if (bf > 1 && __balanceFactor(x->left) < 0) {
        __setLeftChild(x, __rotateLeft(x->left));
        return __rotateRight(x);
    } else if (bf < -1 && __balanceFactor(x->right) <= 0) {
        return __rotateLeft(x);
    } else if (bf < -1 && __balanceFactor(x->right) > 0) {
        __setRightChild(x, __rotateRight(x->right));
        return __rotateLeft(x);
    }

    return x;
}

struct AVL_Node *__remove(struct AVL *tree, struct AVL_Node *x,
                          struct AVL_Node *z)
{
    struct AVL_Node *y;

    if (__compare(tree, z, x) < 0) {
        __setLeftChild(x, __remove(tree, x->left, z));
    } else if (__compare(tree, z, x) > 0) {
        __setRightChild(x, __remove(tree, x->right, z));
    } else {
        if (x->left == NULL) {
            x = NULL;
        } else if (x->right == NULL) {
            x = x->left;
        } else {
            y = __minimum(x->right);
            x->right = __remove(tree, x->right, y);
            x = __exchange(x, y);
        }
    }

    return __rebalanceRemoval(tree, x);
}

void AVL_Remove(struct AVL *tree, struct AVL_Node *z)
{
    if (__isEmpty(tree))
        return;

    tree->root = __remove(tree, tree->root, z);

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static inline struct AVL_Node *__next(struct AVL_Node *x)
{
    struct AVL_Node *parent;

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

static inline struct AVL_Node *__prev(struct AVL_Node *x)
{
    struct AVL_Node *parent;

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

void AVL_Forward(struct AVL *tree, void (*Call)(struct AVL_Node *, void *),
                 void *private)
{
    struct AVL_Node *x;

    if (__isEmpty(tree))
        return;

    x = __minimum(tree->root);
    while (x != NULL) {
        Call(x, private);
        x = __next(x);
    }
}

void AVL_Backward(struct AVL *tree, void (*Call)(struct AVL_Node *, void *),
                  void *private)
{
    struct AVL_Node *x;

    if (__isEmpty(tree))
        return;

    x = __maximum(tree->root);
    while (x != NULL) {
        Call(x, private);
        x = __prev(x);
    }
}

static void __forEachPreorder(struct AVL_Node *x,
                              void (*Call)(struct AVL_Node *, void *),
                              void *private)
{
    if (x == NULL)
        return;

    Call(x, private);
    __forEachPreorder(x->left, Call, private);
    __forEachPreorder(x->right, Call, private);
}

void AVL_Preorder(struct AVL *tree, void (*Call)(struct AVL_Node *, void *),
                  void *private)
{
    __forEachPreorder(tree->root, Call, private);
}

static void __forEachInorder(struct AVL_Node *x,
                             void (*Call)(struct AVL_Node *, void *),
                             void *private)
{
    if (x == NULL)
        return;

    __forEachInorder(x->left, Call, private);
    Call(x, private);
    __forEachInorder(x->right, Call, private);
}

void AVL_Inorder(struct AVL *tree, void (*Call)(struct AVL_Node *, void *),
                 void *private)
{
    __forEachInorder(tree->root, Call, private);
}

static void __forEachPostorder(struct AVL_Node *x,
                               void (*Call)(struct AVL_Node *, void *),
                               void *private)
{
    if (x == NULL)
        return;

    __forEachPostorder(x->left, Call, private);
    __forEachPostorder(x->right, Call, private);
    Call(x, private);
}

void AVL_Postorder(struct AVL *tree, void (*Call)(struct AVL_Node *, void *),
                   void *private)
{
    __forEachPostorder(tree->root, Call, private);
}
