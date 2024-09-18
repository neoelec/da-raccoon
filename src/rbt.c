// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdbool.h>
#include <stdlib.h>

#include <container/rbt.h>

static inline bool __isEmpty(struct RBT_Node *x)
{
    return x->parent == x ? true : false;
}

static inline void __setEmpty(struct RBT_Node *x) { x->parent = x; }

static inline void __initNode(struct RBT_Node *x, struct RBT_Node *NiL)
{
    x->left = NiL;
    x->right = NiL;
    x->color = RBT_RED;

    __setEmpty(x);
}

void RBT_Init(struct RBT *tree,
    int (*Compare)(const struct RBT_Node *, const struct RBT_Node *))
{
    struct RBT_Node *NiL = &tree->__NiL;

    __initNode(NiL, NiL);
    NiL->color = RBT_BLACK;

    tree->NiL = NiL;
    tree->root = NiL;
    tree->Compare = Compare;
}

static inline struct RBT_Node *__minimum(
    const struct RBT_Node *x, struct RBT_Node *NiL)
{
    if (x == NiL)
        return NiL;

    while (x->left != NiL)
        x = x->left;

    return (struct RBT_Node *)x;
}

struct RBT_Node *RBT_Minimum(const struct RBT *tree)
{
    return __minimum(tree->root, tree->NiL);
}

static inline struct RBT_Node *__maximum(
    const struct RBT_Node *x, struct RBT_Node *NiL)
{
    if (x == NiL)
        return NiL;

    while (x->right != NiL)
        x = x->right;

    return (struct RBT_Node *)x;
}

struct RBT_Node *RBT_Maximum(const struct RBT *tree)
{
    return __maximum(tree->root, tree->NiL);
}

static inline struct RBT_Node *__search(const struct RBT_Node *x,
    const struct RBT_Node *key_node, const struct RBT_Node *NiL,
    int (*Compare)(const struct RBT_Node *, const struct RBT_Node *))
{
    while (x != NiL) {
        int diff = Compare(key_node, x);
        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return (struct RBT_Node *)x;
}

struct RBT_Node *RBT_Search(
    const struct RBT *tree, const struct RBT_Node *key_node)
{
    return __search(tree->root, key_node, tree->NiL, tree->Compare);
}

static inline void __rotateLeft(
    struct RBT *tree, struct RBT_Node *x, const struct RBT_Node *NiL)
{
    struct RBT_Node *y = x->right;

    x->right = y->left;

    if (y->left != NiL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NiL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

static inline void __rotateRight(
    struct RBT *tree, struct RBT_Node *x, const struct RBT_Node *NiL)
{
    struct RBT_Node *y = x->left;

    x->left = y->right;

    if (y->right != NiL)
        y->right->parent = x;

    y->parent = x->parent;
    if (x->parent == NiL)
        tree->root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;

    y->right = x;
    x->parent = y;
}

static inline void __fixUpInsertion(
    struct RBT *tree, struct RBT_Node *z, const struct RBT_Node *NiL)
{
    while (z->parent->color == RBT_RED) {
        if (z->parent == z->parent->parent->left) {
            struct RBT_Node *y = z->parent->parent->right;

            if (y->color == RBT_RED) {
                z->parent->color = RBT_BLACK;
                y->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    __rotateLeft(tree, z, NiL);
                }

                z->parent->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                __rotateRight(tree, z->parent->parent, NiL);
            }
        } else {
            struct RBT_Node *y = z->parent->parent->left;

            if (y->color == RBT_RED) {
                z->parent->color = RBT_BLACK;
                y->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    __rotateRight(tree, z, NiL);
                }
                z->parent->color = RBT_BLACK;
                z->parent->parent->color = RBT_RED;
                __rotateLeft(tree, z->parent->parent, NiL);
            }
        }
    }

    tree->root->color = RBT_BLACK;
}

static inline void __insert(struct RBT *tree, struct RBT_Node *z,
    struct RBT_Node *NiL,
    int (*Compare)(const struct RBT_Node *, const struct RBT_Node *))
{
    struct RBT_Node *y = NiL;
    struct RBT_Node *temp = tree->root;

    __initNode(z, NiL);

    while (temp != NiL) {
        y = temp;
        temp = Compare(z, y) < 0 ? temp->left : temp->right;
    }

    z->parent = y;

    if (y == NiL)
        tree->root = z;
    else {
        if (Compare(z, y) < 0)
            y->left = z;
        else
            y->right = z;
    }

    z->right = NiL;
    z->left = NiL;

    __fixUpInsertion(tree, z, NiL);
}

void RBT_Insert(struct RBT *tree, struct RBT_Node *z)
{
    __insert(tree, z, tree->NiL, tree->Compare);

    if (tree->root != tree->NiL)
        tree->root->parent = tree->NiL;
}

static inline void __shiftNodes(
    struct RBT *tree, struct RBT_Node *u, struct RBT_Node *v)
{
    if (u->parent == tree->NiL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v != tree->NiL)
        v->parent = u->parent;
}

static inline void __fixUpDeletion(
    struct RBT *tree, struct RBT_Node *x, const struct RBT_Node *NiL)
{
    while (x != tree->root && x->color == RBT_BLACK) {
        if (x == x->parent->left) {
            struct RBT_Node *w = x->parent->right;
            if (w->color == RBT_RED) {
                w->color = RBT_BLACK;
                x->parent->color = RBT_RED;
                __rotateLeft(tree, x->parent, NiL);
                w = x->parent->right;
            }

            if (w->left->color == RBT_BLACK && w->right->color == RBT_BLACK) {
                w->color = RBT_RED;
                x = x->parent;
            } else {
                if (w->right->color == RBT_BLACK) {
                    w->left->color = RBT_BLACK;
                    w->color = RBT_RED;
                    __rotateRight(tree, w, NiL);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = RBT_BLACK;
                w->right->color = RBT_BLACK;
                __rotateLeft(tree, x->parent, NiL);
                x = tree->root;
            }
        } else {
            struct RBT_Node *w = x->parent->left;
            if (w->color == RBT_RED) {
                w->color = RBT_BLACK;
                x->parent->color = RBT_RED;
                __rotateRight(tree, x->parent, NiL);
                w = x->parent->left;
            }

            if (w->right->color == RBT_BLACK && w->left->color == RBT_BLACK) {
                w->color = RBT_RED;
                x = x->parent;
            } else {
                if (w->left->color == RBT_BLACK) {
                    w->right->color = RBT_BLACK;
                    w->color = RBT_RED;
                    __rotateLeft(tree, w, NiL);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = RBT_BLACK;
                w->left->color = RBT_BLACK;
                __rotateRight(tree, x->parent, NiL);
                x = tree->root;
            }
        }
    }

    x->color = RBT_BLACK;
}

static inline void __remove(
    struct RBT *tree, struct RBT_Node *d, struct RBT_Node *NiL)
{
    struct RBT_Node *y = d;
    struct RBT_Node *x;
    enum RBT_Color y_orignal_color = y->color;

    if (d->left == NiL) {
        x = d->right;
        __shiftNodes(tree, d, d->right);
    } else if (d->right == NiL) {
        x = d->left;
        __shiftNodes(tree, d, d->left);
    } else {
        y = __maximum(d->right, NiL);
        y_orignal_color = y->color;
        x = y->right;
        if (y->parent == d) {
            x->parent = d;
        } else {
            __shiftNodes(tree, y, y->right);
            y->right = d->right;
            y->right->parent = y;
        }

        __shiftNodes(tree, d, y);
        y->left = d->left;
        y->left->parent = y;
        y->color = d->color;
    }

    if (y_orignal_color == RBT_BLACK)
        __fixUpDeletion(tree, x, NiL);
}

void RBT_Remove(struct RBT *tree, struct RBT_Node *d)
{
    __remove(tree, d, tree->NiL);

    d->parent = d;

    if (tree->root != tree->NiL)
        tree->root->parent = tree->NiL;
}

static inline struct RBT_Node *__next(struct RBT_Node *x, struct RBT_Node *NiL)
{
    struct RBT_Node *parent;

    if (__isEmpty(x))
        return NiL;

    if (x->right != NiL) {
        x = x->right;
        while (x->left != NiL)
            x = x->left;

        return x;
    }

    parent = x->parent;
    while ((parent != NiL) && (x == parent->right)) {
        x = parent;
        parent = x->parent;
    }

    return parent;
}

static inline struct RBT_Node *__prev(struct RBT_Node *x, struct RBT_Node *NiL)
{
    struct RBT_Node *parent;

    if (__isEmpty(x))
        return NiL;

    if (x->left != NiL) {
        x = x->left;
        while (x->right != NiL)
            x = x->right;

        return x;
    }

    parent = x->parent;
    while ((parent != NiL) && (x == parent->left)) {
        x = parent;
        parent = x->parent;
    }

    return parent;
}

void RBT_Forward(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    struct RBT_Node *NiL = tree->NiL;
    struct RBT_Node *x = __minimum(tree->root, NiL);

    while (x != NiL) {
        Call(x, private);
        x = __next(x, NiL);
    }
}

void RBT_Backward(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    struct RBT_Node *NiL = tree->NiL;
    struct RBT_Node *x = __maximum(tree->root, NiL);

    while (x != NiL) {
        Call(x, private);
        x = __prev(x, NiL);
    }
}

static void __forEachPreorder(struct RBT_Node *node, const struct RBT_Node *NiL,
    void (*Call)(struct RBT_Node *, void *), void *private)
{
    if (node == NiL)
        return;

    Call(node, private);
    __forEachPreorder(node->left, NiL, Call, private);
    __forEachPreorder(node->right, NiL, Call, private);
}

void RBT_Preorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    __forEachPreorder(tree->root, tree->NiL, Call, private);
}

static void __forEachInorder(struct RBT_Node *node, const struct RBT_Node *NiL,
    void (*Call)(struct RBT_Node *, void *), void *private)
{
    if (node == NiL)
        return;

    __forEachInorder(node->left, NiL, Call, private);
    Call(node, private);
    __forEachInorder(node->right, NiL, Call, private);
}

void RBT_Inorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    __forEachInorder(tree->root, tree->NiL, Call, private);
}

static void __forEachPostorder(struct RBT_Node *node,
    const struct RBT_Node *NiL, void (*Call)(struct RBT_Node *, void *),
    void *private)
{
    if (node == NiL)
        return;

    __forEachPostorder(node->left, NiL, Call, private);
    __forEachPostorder(node->right, NiL, Call, private);
    Call(node, private);
}

void RBT_Postorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private)
{
    __forEachPostorder(tree->root, tree->NiL, Call, private);
}
