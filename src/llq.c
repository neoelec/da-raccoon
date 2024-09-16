// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/llq.h>

static inline size_t __count(const struct LLQ *queue) { return queue->count; }

static inline bool __isEmpty(const struct LLQ *queue)
{
    return queue->count == 0;
}

static inline void __insertFront(struct LLQ *queue, struct DLL_Node *node)
{
    DLL_Init(node);
    queue->count++;
    DLL_InsertAfter(&queue->head, node);
}

static inline void __insertRear(struct LLQ *queue, struct DLL_Node *node)
{
    DLL_Init(node);
    queue->count++;
    DLL_InsertBefore(&queue->head, node);
}

static inline struct DLL_Node *__removeFront(struct LLQ *queue)
{
    struct DLL_Node *node;

    if (__isEmpty(queue))
        return NULL;

    node = queue->head.next;

    queue->count--;
    DLL_Remove(node);

    return node;
}

static inline struct DLL_Node *__removeRear(struct LLQ *queue)
{
    struct DLL_Node *node;

    if (__isEmpty(queue))
        return NULL;

    node = queue->head.prev;

    queue->count--;
    DLL_Remove(node);

    return node;
}

void LLQ_Init(struct LLQ *queue)
{
    queue->count = 0;
    DLL_Init(&queue->head);
}

void LLQ_Enqueue(struct LLQ *queue, struct DLL_Node *node)
{
    __insertRear(queue, node);
}

void LLQ_InsertFront(struct LLQ *queue, struct DLL_Node *node)
{
    __insertFront(queue, node);
}

void LLQ_InsertRear(struct LLQ *queue, struct DLL_Node *node)
{
    __insertRear(queue, node);
}

struct DLL_Node *LLQ_Dequeue(struct LLQ *queue) { return __removeFront(queue); }

struct DLL_Node *LLQ_RemoveFront(struct LLQ *queue)
{
    return __removeFront(queue);
}

struct DLL_Node *LLQ_RemoveRear(struct LLQ *queue)
{
    return __removeRear(queue);
}

size_t LLQ_Count(const struct LLQ *queue) { return __count(queue); }

bool LLQ_IsEmpty(const struct LLQ *queue) { return __isEmpty(queue); }

struct DLL_Node *LLQ_Front(const struct LLQ *queue)
{
    if (__isEmpty(queue))
        return NULL;

    return queue->head.next;
}

struct DLL_Node *LLQ_Rear(const struct LLQ *queue)
{
    if (__isEmpty(queue))
        return NULL;

    return queue->head.prev;
}

void LLQ_Forward(
    struct LLQ *queue, void (*Call)(struct DLL_Node *, void *), void *private)
{
    DLL_Forward(&queue->head, Call, private);
}
