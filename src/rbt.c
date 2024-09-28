// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdbool.h>
#include <stdlib.h>

#include <container/rbt.h>

#define __compare(tree, a, b) (tree)->Compare(a, b)

void RBT_Init(struct RBT *tree,
    int (*Compare)(const struct RBT_Node *, const struct RBT_Node *))
{
    struct RBT_Node *NiL = &tree->__NiL;

    NiL->left = tree->NiL;
    NiL->right = tree->NiL;
    NiL->color = RBT_BLACK;

    tree->NiL = NiL;
    tree->root = NiL;
    tree->Compare = Compare;
}

static inline bool __isEmpty(const struct RBT *tree)
{
    return (tree->root == tree->NiL) ? true : false;
}

bool RBT_IsEmpty(const struct RBT *tree) { return __isEmpty(tree); }

static inline struct RBT_Node *__minimum(
    const struct RBT *tree, const struct RBT_Node *x)
{
    while (x->left != tree->NiL)
        x = x->left;

    return (struct RBT_Node *)x;
}

struct RBT_Node *RBT_Minimum(const struct RBT *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __minimum(tree, tree->root);
}

static inline struct RBT_Node *__maximum(
    const struct RBT *tree, const struct RBT_Node *x)
{
    while (x->right != tree->NiL)
        x = x->right;

    return (struct RBT_Node *)x;
}

struct RBT_Node *RBT_Maximum(const struct RBT *tree)
{
    if (__isEmpty(tree))
        return NULL;

    return __maximum(tree, tree->root);
}

static inline struct RBT_Node *__search(
    const struct RBT *tree, const struct RBT_Node *x, const struct RBT_Node *k)
{
    while (x != tree->NiL) {
        int diff = __compare(tree, k, x);
        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return (struct RBT_Node *)x;
}

struct RBT_Node *RBT_Search(const struct RBT *tree, const struct RBT_Node *k)
{
    struct RBT_Node *x = __search(tree, tree->root, k);

    return x == tree->NiL ? NULL : x;
}

static inline void __rotateLeft(struct RBT *tree, struct RBT_Node *x)
{
    struct RBT_Node *y;

    y = x->right;
    x->right = y->left;

    if (y->left != tree->NiL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == tree->NiL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

static inline void __rotateRight(struct RBT *tree, struct RBT_Node *x)
{
    struct RBT_Node *y;

    y = x->left;
    x->left = y->right;

    if (y->right != tree->NiL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == tree->NiL)
        tree->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

static inline void __fixUpInsertion(struct RBT *tree, struct RBT_Node *z)
{
    struct RBT_Node *y;

    while (z->parent->color == RBT_RED) {
        if (z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;

            if (y->color == RBT_RED) {
                /* Case 1. */
                z->parent->color = RBT_BLACK;
                y->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    /* Case 2. */
                    z = z->parent;
                    __rotateLeft(tree, z);
                }

                /* Case 3. */
                z->parent->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                __rotateRight(tree, z->parent->parent);
            }
        } else { /* same as previous, but with "right" and "left" exchanged. */
            y = z->parent->parent->left;

            if (y->color == RBT_RED) {
                z->parent->color = RBT_BLACK;
                y->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    __rotateRight(tree, z);
                }

                z->parent->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                __rotateLeft(tree, z->parent->parent);
            }
        }
    }

    tree->root->color = RBT_BLACK;
}

static inline void __insert(struct RBT *tree, struct RBT_Node *z)
{
    struct RBT_Node *y;
    struct RBT_Node *x;

    x = tree->root;
    y = tree->NiL;

    while (x != tree->NiL) {
        y = x;
        x = __compare(tree, z, x) < 0 ? x->left : x->right;
    }

    z->parent = y;

    if (y == tree->NiL)
        tree->root = z;
    else if (__compare(tree, z, y) < 0)
        y->left = z;
    else
        y->right = z;

    z->left = tree->NiL;
    z->right = tree->NiL;
    z->color = RBT_RED;

    __fixUpInsertion(tree, z);
}

void RBT_Insert(struct RBT *tree, struct RBT_Node *z)
{
    __insert(tree, z);

    if (tree->root != tree->NiL)
        tree->root->parent = tree->NiL;
}

static inline void __transplant(
    struct RBT *tree, struct RBT_Node *u, struct RBT_Node *v)
{
    if (u->parent == tree->NiL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

static inline void __fixUpRemoval(struct RBT *tree, struct RBT_Node *x)
{
    struct RBT_Node *w;

    while (x != tree->root && x->color == RBT_BLACK) {
        if (x == x->parent->left) {
            w = x->parent->right;

            if (w->color == RBT_RED) {
                /* Case 1. */
                w->color = RBT_BLACK;
                x->parent->color = RBT_RED;
                __rotateLeft(tree, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == RBT_BLACK && w->right->color == RBT_BLACK) {
                /* Case 2. */
                w->color = RBT_RED;
                x = x->parent;
            } else {
                if (w->right->color == RBT_BLACK) {
                    /* Case 3. */
                    w->left->color = RBT_BLACK;
                    w->color = RBT_RED;
                    __rotateRight(tree, w);
                    w = x->parent->right;
                }

                /* Case 4. */
                w->color = x->parent->color;
                x->parent->color = RBT_BLACK;
                w->right->color = RBT_BLACK;
                __rotateLeft(tree, x->parent);
                x = tree->root;
            }
        } else { /* same as previous, but with "right" and "left" exchanged. */
            w = x->parent->left;

            if (w->color == RBT_RED) {
                w->color = RBT_BLACK;
                x->parent->color = RBT_RED;
                __rotateRight(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == RBT_BLACK && w->left->color == RBT_BLACK) {
                w->color = RBT_RED;
                x = x->parent;
            } else {
                if (w->left->color == RBT_BLACK) {
                    w->right->color = RBT_BLACK;
                    w->color = RBT_RED;
                    __rotateLeft(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = RBT_BLACK;
                w->left->color = RBT_BLACK;
                __rotateRight(tree, x->parent);
                x = tree->root;
            }
        }
    }

    x->color = RBT_BLACK;
}

static inline void __remove(struct RBT *tree, struct RBT_Node *z)
{
    struct RBT_Node *y;
    struct RBT_Node *x;
    enum RBT_Color y_orignal_color;

    y = z;
    y_orignal_color = y->color;

    if (z->left == tree->NiL) {
        x = z->right;
        __transplant(tree, z, z->right);
    } else if (z->right == tree->NiL) {
        x = z->left;
        __transplant(tree, z, z->left);
    } else {
        y = __minimum(tree, z->right); /* successor */
        y_orignal_color = y->color;
        x = y->right;
        if (y != z->right) {
            __transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        } else
            x->parent = y;

        __transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_orignal_color == RBT_BLACK)
        __fixUpRemoval(tree, x);
}

void RBT_Remove(struct RBT *tree, struct RBT_Node *z)
{
    __remove(tree, z);

    z->parent = z;

    if (tree->root != tree->NiL)
        tree->root->parent = tree->NiL;
}

static inline struct RBT_Node *__next(
    const struct RBT *tree, struct RBT_Node *x)
{
    struct RBT_Node *parent;

    if (x->right != tree->NiL) {
        x = x->right;
        while (x->left != tree->NiL)
            x = x->left;

        return x;
    }

    parent = x->parent;
    while ((parent != tree->NiL) && (x == parent->right)) {
        x = parent;
        parent = x->parent;
    }

    return parent;
}

static inline struct RBT_Node *__prev(
    const struct RBT *tree, struct RBT_Node *x)
{
    struct RBT_Node *parent;

    if (x->left != tree->NiL) {
        x = x->left;
        while (x->right != tree->NiL)
            x = x->right;

        return x;
    }

    parent = x->parent;
    while ((parent != tree->NiL) && (x == parent->left)) {
        x = parent;
        parent = x->parent;
    }

    return parent;
}

void RBT_Forward(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    struct RBT_Node *x = __minimum(tree, tree->root);

    while (x != tree->NiL) {
        Call(x, private);
        x = __next(tree, x);
    }
}

void RBT_Backward(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    struct RBT_Node *x = __maximum(tree, tree->root);

    while (x != tree->NiL) {
        Call(x, private);
        x = __prev(tree, x);
    }
}

static void __forEachPreorder(const struct RBT *tree, struct RBT_Node *x,
    void (*Call)(struct RBT_Node *, void *), void *private)
{
    if (x == tree->NiL)
        return;

    Call(x, private);
    __forEachPreorder(tree, x->left, Call, private);
    __forEachPreorder(tree, x->right, Call, private);
}

void RBT_Preorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    __forEachPreorder(tree, tree->root, Call, private);
}

static void __forEachInorder(const struct RBT *tree, struct RBT_Node *x,
    void (*Call)(struct RBT_Node *, void *), void *private)
{
    if (x == tree->NiL)
        return;

    __forEachInorder(tree, x->left, Call, private);
    Call(x, private);
    __forEachInorder(tree, x->right, Call, private);
}

void RBT_Inorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    __forEachInorder(tree, tree->root, Call, private);
}

static void __forEachPostorder(const struct RBT *tree, struct RBT_Node *x,
    void (*Call)(struct RBT_Node *, void *), void *private)
{
    if (x == tree->NiL)
        return;

    __forEachPostorder(tree, x->left, Call, private);
    __forEachPostorder(tree, x->right, Call, private);
    Call(x, private);
}

void RBT_Postorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    __forEachPostorder(tree, tree->root, Call, private);
}
