// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Linked List Stack */
#ifndef __LLS_H__
#define __LLS_H__

#include <stdbool.h>

#include "common.h"
#include "sll.h"

struct LLS {
    size_t count;
    struct SLL_Node head;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void LLS_Init(struct LLS *stack);
extern void LLS_Push(struct LLS *stack, struct SLL_Node *node);
extern struct SLL_Node *LLS_Pop(struct LLS *stack);
extern struct SLL_Node *LLS_Top(const struct LLS *stack);
extern size_t LLS_Count(const struct LLS *stack);
extern bool LLS_IsEmpty(const struct LLS *stack);
extern void LLS_Forward(struct LLS *stack,
                        void (*Call)(struct SLL_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __LLS_H__ */
