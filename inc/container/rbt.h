// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Red Black Tree */
#ifndef __RBT_H__
#define __RBT_H__

#include <stdbool.h>
#include <stddef.h>

#include "common.h"

enum RBT_Color { RBT_RED = 0, RBT_BLACK };

struct RBT_Node {
    struct RBT_Node *parent;
    struct RBT_Node *right;
    struct RBT_Node *left;
    enum RBT_Color color;
};

struct RBT {
    struct RBT_Node *root;
    struct RBT_Node *NiL;
    struct RBT_Node __NiL;
    int (*Compare)(const struct RBT_Node *, const struct RBT_Node *);
};

#ifdef __cplusplus
extern "C" {
#endif

extern void RBT_Init(struct RBT *tree,
    int (*Compare)(const struct RBT_Node *, const struct RBT_Node *));
extern bool RBT_IsEmpty(const struct RBT *tree);
extern struct RBT_Node *RBT_Minimum(const struct RBT *root);
extern struct RBT_Node *RBT_Maximum(const struct RBT *root);
extern struct RBT_Node *RBT_Search(
    const struct RBT *tree, const struct RBT_Node *key_node);
extern void RBT_Insert(struct RBT *tree, struct RBT_Node *node);
extern void RBT_Remove(struct RBT *tree, struct RBT_Node *node);
extern void RBT_Forward(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private);
extern void RBT_Backward(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private);
extern void RBT_Preorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private);
extern void RBT_Inorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private);
extern void RBT_Postorder(
    struct RBT *tree, void (*Call)(struct RBT_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __RBT_H__ */
