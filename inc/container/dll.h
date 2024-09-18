// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Doubly Linked List */
#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>
#include <sys/types.h>

#include "common.h"

struct DLL_Node {
    struct DLL_Node *prev;
    struct DLL_Node *next;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void DLL_Init(struct DLL_Node *head);
extern void DLL_InsertHead(struct DLL_Node *head, struct DLL_Node *node);
extern void DLL_InsertTail(struct DLL_Node *head, struct DLL_Node *node);
extern void DLL_Remove(struct DLL_Node *node);
extern size_t DLL_Count(const struct DLL_Node *head);
extern struct DLL_Node *DLL_GetNode(const struct DLL_Node *head, ssize_t n);
extern void DLL_Forward(struct DLL_Node *head,
    void (*Call)(struct DLL_Node *, void *), void *private);
extern void DLL_Backward(struct DLL_Node *head,
    void (*Call)(struct DLL_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif

static inline void DLL_InsertAfter(struct DLL_Node *pos, struct DLL_Node *node)
{
    pos->next->prev = node;
    node->next = pos->next;
    pos->next = node;
    node->prev = pos;
}

static inline void DLL_InsertBefore(struct DLL_Node *pos, struct DLL_Node *node)
{
    pos->prev->next = node;
    node->prev = pos->prev;
    pos->prev = node;
    node->next = pos;
}

#endif /* __DLL_H__ */
