// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Splay Tree */
#ifndef __SPLT_H__
#define __SPLT_H__

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "common.h"

struct SPLT_Node {
    struct SPLT_Node *parent;
    struct SPLT_Node *right;
    struct SPLT_Node *left;
};

struct SPLT {
    struct SPLT_Node *root;
    int (*Compare)(const struct SPLT_Node *, const struct SPLT_Node *);
};

#ifdef __cplusplus
extern "C" {
#endif

extern void SPLT_Init(struct SPLT *tree,
    int (*Compare)(const struct SPLT_Node *, const struct SPLT_Node *));
extern bool SPLT_IsEmpty(const struct SPLT *tree);
extern struct SPLT_Node *SPLT_Minimum(const struct SPLT *tree);
extern struct SPLT_Node *SPLT_Maximum(const struct SPLT *tree);
extern struct SPLT_Node *SPLT_Search(
    const struct SPLT *tree, const struct SPLT_Node *k);
extern void SPLT_Insert(struct SPLT *tree, struct SPLT_Node *x);
extern void SPLT_Remove(struct SPLT *tree, struct SPLT_Node *x);
extern void SPLT_Forward(
    struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *), void *private);
extern void SPLT_Backward(
    struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *), void *private);
extern void SPLT_Preorder(
    struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *), void *private);
extern void SPLT_Inorder(
    struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *), void *private);
extern void SPLT_Postorder(
    struct SPLT *tree, void (*Call)(struct SPLT_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __SPLT_H__ */
