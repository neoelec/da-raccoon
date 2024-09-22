// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdbool.h>
#include <stdlib.h>

#include <container/avl.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

static inline bool __isEmpty(struct AVL_Node *x)
{
    return x->parent == x ? true : false;
}

static inline void __initNode(struct AVL_Node *x)
{
    x->parent = x;
    x->left = NULL;
    x->right = NULL;
    x->height = 0;
}

void AVL_Init(struct AVL *tree,
    int (*Compare)(const struct AVL_Node *, const struct AVL_Node *))
{
    tree->root = NULL;
    tree->Compare = Compare;
}

static inline void __setParent(struct AVL_Node *x)
{
    if (x == NULL)
        return;

    if (x->left)
        x->left->parent = x;

    if (x->right)
        x->right->parent = x;
}

static inline ssize_t __height(struct AVL_Node *x)
{
    if (x == NULL)
        return 0;

    return x->height;
}

static inline struct AVL_Node *__rotateLeft(struct AVL_Node *x)
{
    struct AVL_Node *y = x->right;
    struct AVL_Node *t2 = y->left;

    y->left = x;
    __setParent(y);
    x->right = t2;
    __setParent(x);

    x->height = max(__height(x->left), __height(x->right)) + 1;
    y->height = max(__height(y->left), __height(y->right)) + 1;

    return y;
}

static inline struct AVL_Node *__rotateRight(struct AVL_Node *y)
{
    struct AVL_Node *x = y->left;
    struct AVL_Node *t2 = x->right;

    x->right = y;
    __setParent(x);
    y->left = t2;
    __setParent(y);

    y->height = max(__height(y->left), __height(y->right)) + 1;
    x->height = max(__height(x->left), __height(x->right)) + 1;

    return x;
}

static inline ssize_t __balanceFactor(struct AVL_Node *x)
{
    if (x == NULL)
        return 0;

    return __height(x->left) - __height(x->right);
}

static inline struct AVL_Node *__minimum(const struct AVL_Node *x)
{
    if (x == NULL)
        return NULL;

    while (x->left != NULL)
        x = x->left;

    return (struct AVL_Node *)x;
}

static inline struct AVL_Node *__maximum(const struct AVL_Node *x)
{
    if (x == NULL)
        return NULL;

    while (x->right != NULL)
        x = x->right;

    return (struct AVL_Node *)x;
}

static struct AVL_Node *__insert(struct AVL_Node *x, struct AVL_Node *z,
    int (*Compare)(const struct AVL_Node *, const struct AVL_Node *))
{
    ssize_t bf;

    __initNode(z);

    if (x == NULL) {
        x = z;
    } else if (Compare(z, x) < 0) {
        x->left = __insert(x->left, z, Compare);
        __setParent(x);
    } else if (Compare(z, x) > 0) {
        x->right = __insert(x->right, z, Compare);
        __setParent(x);
    } else {
        return x;
    }

    x->height = max(__height(x->left), __height(x->right)) + 1;

    bf = __balanceFactor(x);
    if (bf > 1 && Compare(z, x->left) < 0) { // left left case
        return __rotateRight(x);
    } else if (bf < -1 && Compare(z, x->right) > 0) { // right right case
        return __rotateLeft(x);
    } else if (bf > 1 && Compare(z, x->left) > 0) { // left right case
        x->left = __rotateLeft(x->left);
        __setParent(x);
        return __rotateRight(x);
    } else if (bf < -1 && Compare(z, x->right) < 0) { // right left case
        x->right = __rotateRight(x->right);
        __setParent(x);
        return __rotateLeft(x);
    }

    return x;
}

void AVL_Insert(struct AVL *tree, struct AVL_Node *z)
{
    tree->root = __insert(tree->root, z, tree->Compare);

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

static inline struct AVL_Node *__replaceNode(
    const struct AVL_Node *a, struct AVL_Node *b)
{
    struct AVL_Node *parent;

    b->parent = parent = a->parent;
    b->left = a->left;
    b->right = a->right;
    b->height = a->height;
    __setParent(b);

    if (parent) {
        if (parent->right == a)
            parent->right = b;
        else
            parent->left = b;
    }

    return b;
}

struct AVL_Node *__remove(struct AVL_Node *x, struct AVL_Node *d,
    int (*Compare)(const struct AVL_Node *, const struct AVL_Node *))
{
    ssize_t bf;

    if (x == NULL)
        return NULL;

    if (Compare(d, x) < 0) {
        x->left = __remove(x->left, d, Compare);
        __setParent(x);
    } else if (Compare(d, x) > 0) {
        x->right = __remove(x->right, d, Compare);
        __setParent(x);
    } else {
        if ((x->left == NULL) || (x->right == NULL)) {
            struct AVL_Node *temp = NULL;

            if (temp == x->left)
                temp = x->right;
            else
                temp = x->left;

            if (temp == NULL) {
                temp = x;
                x = NULL;
            } else {
                x = temp;
            }
        } else {
            struct AVL_Node *temp = __minimum(x->right);

            x->right = __remove(x->right, temp, Compare);
            x = __replaceNode(x, temp);
        }
    }

    if (x == NULL)
        return x;

    x->height = max(__height(x->left), __height(x->right)) + 1;

    bf = __balanceFactor(x);
    if (bf > 1 && __balanceFactor(x->left) >= 0) {
        return __rotateRight(x);
    } else if (bf > 1 && __balanceFactor(x->left) < 0) {
        x->left = __rotateLeft(x->left);
        __setParent(x);
        return __rotateRight(x);
    } else if (bf < -1 && __balanceFactor(x->right) <= 0) {
        return __rotateLeft(x);
    } else if (bf < -1 && __balanceFactor(x->right) > 0) {
        x->right = __rotateRight(x->right);
        __setParent(x);
        return __rotateLeft(x);
    }

    return x;
}

void AVL_Remove(struct AVL *tree, struct AVL_Node *d)
{
    tree->root = __remove(tree->root, d, tree->Compare);

    if (tree->root != NULL)
        tree->root->parent = NULL;
}

struct AVL_Node *AVL_Minimum(const struct AVL *tree)
{
    return __minimum(tree->root);
}

struct AVL_Node *AVL_Maximum(const struct AVL *tree)
{
    return __maximum(tree->root);
}

static inline struct AVL_Node *__search(const struct AVL_Node *x,
    const struct AVL_Node *key_node,
    int (*Compare)(const struct AVL_Node *, const struct AVL_Node *))
{
    while (x != NULL) {
        int diff = Compare(key_node, x);
        if (diff == 0)
            break;

        x = diff < 0 ? x->left : x->right;
    }

    return (struct AVL_Node *)x;
}

struct AVL_Node *AVL_Search(
    const struct AVL *tree, const struct AVL_Node *key_node)
{
    return __search(tree->root, key_node, tree->Compare);
}

static inline struct AVL_Node *__next(struct AVL_Node *x)
{
    struct AVL_Node *parent;

    if (__isEmpty(x))
        return NULL;

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

    if (__isEmpty(x))
        return NULL;

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

void AVL_Forward(
    struct AVL *tree, void (*Call)(struct AVL_Node *, void *), void *private)
{
    struct AVL_Node *x = __minimum(tree->root);

    while (x != NULL) {
        Call(x, private);
        x = __next(x);
    }
}

void AVL_Backward(
    struct AVL *tree, void (*Call)(struct AVL_Node *, void *), void *private)
{
    struct AVL_Node *x = __maximum(tree->root);

    while (x != NULL) {
        Call(x, private);
        x = __prev(x);
    }
}

static void __forEachPreorder(
    struct AVL_Node *x, void (*Call)(struct AVL_Node *, void *), void *private)
{
    if (x == NULL)
        return;

    Call(x, private);
    __forEachPreorder(x->left, Call, private);
    __forEachPreorder(x->right, Call, private);
}

void AVL_Preorder(
    struct AVL *tree, void (*Call)(struct AVL_Node *, void *), void *private)
{
    __forEachPreorder(tree->root, Call, private);
}

static void __forEachInorder(
    struct AVL_Node *x, void (*Call)(struct AVL_Node *, void *), void *private)
{
    if (x == NULL)
        return;

    __forEachInorder(x->left, Call, private);
    Call(x, private);
    __forEachInorder(x->right, Call, private);
}

void AVL_Inorder(
    struct AVL *tree, void (*Call)(struct AVL_Node *, void *), void *private)
{
    __forEachInorder(tree->root, Call, private);
}

static void __forEachPostorder(
    struct AVL_Node *x, void (*Call)(struct AVL_Node *, void *), void *private)
{
    if (x == NULL)
        return;

    __forEachPostorder(x->left, Call, private);
    __forEachPostorder(x->right, Call, private);
    Call(x, private);
}

void AVL_Postorder(
    struct AVL *tree, void (*Call)(struct AVL_Node *, void *), void *private)
{
    __forEachPostorder(tree->root, Call, private);
}
