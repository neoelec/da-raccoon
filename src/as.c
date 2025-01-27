// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <errno.h>

#include <container/as.h>

static inline size_t __count(const struct AS *stack)
{
    return stack->top + 1;
}

static inline bool __isEmpty(const struct AS *stack)
{
    return stack->top == -1;
}

static inline bool __isFull(const struct AS *stack)
{
    return __count(stack) == stack->nr_entries;
}

void AS_Init(struct AS *stack, size_t nr_entries)
{
    stack->nr_entries = nr_entries;
    stack->top = -1;
}

int AS_Push(struct AS *stack, void *entry)
{
    if (__isFull(stack))
        return -EIO;

    stack->entry[++stack->top] = entry;

    return 0;
}

void *AS_Pop(struct AS *stack)
{
    return __isEmpty(stack) ? NULL : stack->entry[stack->top--];
}

void *AS_Top(const struct AS *stack)
{
    return __isEmpty(stack) ? NULL : stack->entry[stack->top];
}

size_t AS_Count(const struct AS *stack)
{
    return __count(stack);
}

bool AS_IsEmpty(const struct AS *stack)
{
    return __isEmpty(stack);
}

bool AS_IsFull(const struct AS *stack)
{
    return __isFull(stack);
}

void AS_Forward(struct AS *stack, void (*Call)(void *, void *), void *private)
{
    ssize_t i;

    for (i = 0; i <= stack->top; i++)
        Call(stack->entry[i], private);
}
