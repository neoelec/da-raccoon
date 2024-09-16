// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/lls.h>

static inline size_t __count(const struct LLS *stack) { return stack->count; }

static inline bool __isEmpty(const struct LLS *stack)
{
    return stack->count == 0;
}

void LLS_Init(struct LLS *stack)
{
    stack->count = 0;
    SLL_Init(&stack->head);
}

void LLS_Push(struct LLS *stack, struct SLL_Node *node)
{
    stack->count++;
    SLL_InsertAfter(&stack->head, node);
}

struct SLL_Node *LLS_Pop(struct LLS *stack)
{
    struct SLL_Node *node = stack->head.next;

    if (__isEmpty(stack))
        return NULL;

    stack->count--;
    SLL_Remove(&stack->head, node);

    return node;
}

struct SLL_Node *LLS_Top(const struct LLS *stack) { return stack->head.next; }

size_t LLS_Count(const struct LLS *stack) { return __count(stack); }

bool LLS_IsEmpty(const struct LLS *stack) { return __isEmpty(stack); }

void LLS_Forward(
    struct LLS *stack, void (*Call)(struct SLL_Node *, void *), void *private)
{
    SLL_Forward(&stack->head, Call, private);
}
