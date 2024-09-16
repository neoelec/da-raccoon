// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Singly Linked List */
#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h>
#include <sys/types.h>

#include "common.h"

struct SLL_Node {
    struct SLL_Node *next;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void SLL_Init(struct SLL_Node *head);
extern void SLL_InsertTail(struct SLL_Node *head, struct SLL_Node *node);
extern void SLL_InsertAfter(struct SLL_Node *pos, struct SLL_Node *node);
extern void SLL_Remove(struct SLL_Node *head, struct SLL_Node *node);
extern size_t SLL_Count(const struct SLL_Node *head);
extern struct SLL_Node *SLL_GetNode(const struct SLL_Node *head, ssize_t n);
extern void SLL_Forward(struct SLL_Node *head,
    void (*Call)(struct SLL_Node *, void *), void *private);
extern void SLL_Reverse(struct SLL_Node *head);

#ifdef __cplusplus
}
#endif
#endif /* __SLL_H__ */
