// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Cicular Doubly Linked List */
#ifndef __CDLL_H__
#define __CDLL_H__

#include "common.h"
#include "dll.h"

struct CDLL {
    struct DLL_Node *head;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void CDLL_Init(struct CDLL *list);
extern void CDLL_InsertList(struct CDLL *list, struct DLL_Node *node);
extern void CDLL_InsertTail(struct CDLL *list, struct DLL_Node *node);
extern void CDLL_Remove(struct CDLL *list, struct DLL_Node *node);
extern size_t CDLL_Count(const struct CDLL *list);
extern struct DLL_Node *CDLL_GetNode(const struct CDLL *list, ssize_t n);
extern void CDLL_Forward(
    struct CDLL *list, void (*Call)(struct DLL_Node *, void *), void *private);
extern void CDLL_Backward(
    struct CDLL *list, void (*Call)(struct DLL_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif

static inline void CDLL_InsertAfter(struct DLL_Node *pos, struct DLL_Node *node)
{
    DLL_InsertAfter(pos, node);
}

static inline void CDLL_InsertBefore(
    struct DLL_Node *pos, struct DLL_Node *node)
{
    DLL_InsertBefore(pos, node);
}

#endif /* __CDLL_H__ */
