// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Linked List Queue */
#ifndef __LLQ_H__
#define __LLQ_H__

#include <stdbool.h>

#include "common.h"
#include "dll.h"

struct LLQ {
    size_t count;
    struct DLL_Node head;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void LLQ_Init(struct LLQ *queue);
extern void LLQ_Enqueue(struct LLQ *queue, struct DLL_Node *node);
extern void LLQ_InsertFront(struct LLQ *queue, struct DLL_Node *node);
extern void LLQ_InsertRear(struct LLQ *queue, struct DLL_Node *node);
extern struct DLL_Node *LLQ_Dequeue(struct LLQ *queue);
extern struct DLL_Node *LLQ_RemoveFront(struct LLQ *queue);
extern struct DLL_Node *LLQ_RemoveRear(struct LLQ *queue);
extern size_t LLQ_Count(const struct LLQ *queue);
extern bool LLQ_IsEmpty(const struct LLQ *queue);
extern struct DLL_Node *LLQ_Front(const struct LLQ *queue);
extern struct DLL_Node *LLQ_Rear(const struct LLQ *queue);
extern void LLQ_Forward(
    struct LLQ *queue, void (*Call)(struct DLL_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __LLQ_H__ */
