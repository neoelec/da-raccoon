// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Heap */
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdbool.h>

#include "common.h"

struct Heap {
    size_t order;
    size_t nr_entries;
    size_t used;
    int (*Compare)(const void *, const void *);
    void *entry[0];
};

#define ORDER_MIN 2
#define NR_ENTRIES_MIN HEAP_TO_NR_ENTRIES(ORDER_MIN)

#define HEAP_TO_NR_ENTRIES(__order) ((1 << (__order)) - 1)

#define HEAP_BYTES(nr_entries)                                                 \
    (sizeof(struct Heap) + (nr_entries) * (sizeof(void *)))
#define HEAP_BYTES_MIN HEAP_BYTES(NR_ENTRIES_MIN)

#ifdef __cplusplus
extern "C" {
#endif

extern void Heap_Init(
    struct Heap *heap, int (*Compare)(const void *, const void *));
extern void Heap_InitNrEntries(struct Heap *heap, size_t nr_ntries,
    int (*Compare)(const void *, const void *));
extern void Heap_Insert(struct Heap *heap, void *entry);
extern void *Heap_RemoveHead(struct Heap *heap);
extern void Heap_Forward(
    struct Heap *heap, void (*Call)(void *, void *), void *private);
extern bool Heap_IsEmpty(struct Heap *heap);
extern struct Heap *Heap_Resize(struct Heap *heap);

#ifdef __cplusplus
}
#endif
#endif /* __HEAP_H__ */
