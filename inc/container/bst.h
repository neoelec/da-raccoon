// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Binary Search Tree */
#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>

#include "common.h"

struct BST_Node {
    struct BST_Node *parent;
    struct BST_Node *left;
    struct BST_Node *right;
};

struct BST {
    struct BST_Node *root;
    int (*Compare)(const struct BST_Node *, const struct BST_Node *);
};

#ifdef __cplusplus
extern "C" {
#endif

extern void BST_Init(struct BST *tree,
    int (*Compare)(const struct BST_Node *, const struct BST_Node *));
extern bool BST_IsEmpty(const struct BST *tree);
extern struct BST_Node *BST_Minimum(const struct BST *tree);
extern struct BST_Node *BST_Maximum(const struct BST *tree);
extern struct BST_Node *BST_Search(
    const struct BST *tree, const struct BST_Node *k);
extern void BST_Insert(struct BST *tree, struct BST_Node *x);
extern void BST_Remove(struct BST *tree, struct BST_Node *x);
extern void BST_Forward(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private);
extern void BST_Backward(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private);
extern void BST_Preorder(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private);
extern void BST_Inorder(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private);
extern void BST_Postorder(
    struct BST *tree, void (*Call)(struct BST_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __BST_H__ */
