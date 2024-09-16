// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Simple Binary Tree */
#ifndef __SBT_H__
#define __SBT_H__

#include <stddef.h>

#include "common.h"

struct SBT_Node {
    struct SBT_Node *left;
    struct SBT_Node *right;
};

struct SBT {
    struct SBT_Node *root;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void SBT_Init(struct SBT *tree);
extern void SBT_InitNode(struct SBT_Node *node);
extern void SBT_Preorder(
    struct SBT *tree, void (*Call)(struct SBT_Node *, void *), void *private);
extern void SBT_Inorder(
    struct SBT *tree, void (*Call)(struct SBT_Node *, void *), void *private);
extern void SBT_Postorder(
    struct SBT *tree, void (*Call)(struct SBT_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __SBT_H__ */
