// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Array Stack */
#ifndef __AS_H__
#define __AS_H__

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "common.h"

struct AS {
    size_t nr_entries;
    ssize_t top;
    void *entry[0];
};

#define AS_BYTES(nr_entries)                                                   \
    (sizeof(struct AS) + (nr_entries) * (sizeof(void *)))

#ifdef __cplusplus
extern "C" {
#endif

extern void AS_Init(struct AS *stack, size_t nr_entries);
extern int AS_Push(struct AS *stack, void *x);
extern void *AS_Pop(struct AS *stack);
extern void *AS_Top(const struct AS *stack);
extern size_t AS_Count(const struct AS *stack);
extern bool AS_IsEmpty(const struct AS *stack);
extern bool AS_IsFull(const struct AS *stack);
extern void AS_Forward(
    struct AS *stack, void (*Call)(void *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __AS_H__ */
