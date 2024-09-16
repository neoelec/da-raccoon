// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Left Child Right Sibling Tree */
#ifndef __LCRS_H__
#define __LCRS_H__

#include <stddef.h>

#include "common.h"

struct LCRS_Node {
    union {
        struct LCRS_Node *left;
        struct LCRS_Node *child;
    };
    union {
        struct LCRS_Node *right;
        struct LCRS_Node *sibling;
    };
};

struct LCRS {
    struct LCRS_Node *root;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void LCRS_Init(struct LCRS *tree);
extern void LCRS_InitNode(struct LCRS_Node *node);
extern void LCRS_Chain(struct LCRS_Node *parent, struct LCRS_Node *child);

#ifdef __cplusplus
}
#endif
#endif /* __LCRS_H__ */
