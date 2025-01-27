// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Adelson-Velsky and Landis Tree */
#ifndef __AVL_H__
#define __AVL_H__

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "common.h"

struct AVL_Node {
    struct AVL_Node *parent;
    struct AVL_Node *right;
    struct AVL_Node *left;
    ssize_t height;
};

struct AVL {
    struct AVL_Node *root;
    int (*Compare)(const struct AVL_Node *, const struct AVL_Node *);
};

#ifdef __cplusplus
extern "C" {
#endif

extern void AVL_Init(struct AVL *tree, int (*Compare)(const struct AVL_Node *,
                                                      const struct AVL_Node *));
extern bool AVL_IsEmpty(const struct AVL *tree);
extern struct AVL_Node *AVL_Minimum(const struct AVL *tree);
extern struct AVL_Node *AVL_Maximum(const struct AVL *tree);
extern struct AVL_Node *AVL_Search(const struct AVL *tree,
                                   const struct AVL_Node *k);
extern void AVL_Insert(struct AVL *tree, struct AVL_Node *x);
extern void AVL_Remove(struct AVL *tree, struct AVL_Node *x);
extern void AVL_Forward(struct AVL *tree,
                        void (*Call)(struct AVL_Node *, void *), void *private);
extern void AVL_Backward(struct AVL *tree,
                         void (*Call)(struct AVL_Node *, void *),
                         void *private);
extern void AVL_Preorder(struct AVL *tree,
                         void (*Call)(struct AVL_Node *, void *),
                         void *private);
extern void AVL_Inorder(struct AVL *tree,
                        void (*Call)(struct AVL_Node *, void *), void *private);
extern void AVL_Postorder(struct AVL *tree,
                          void (*Call)(struct AVL_Node *, void *),
                          void *private);

#ifdef __cplusplus
}
#endif
#endif /* __AVL_H__ */
