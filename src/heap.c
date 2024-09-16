// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>
#include <sys/types.h>

#include <container/heap.h>

static inline size_t __toOrder(size_t nr_entries)
{
    size_t order = ORDER_MIN;

    while (nr_entries > HEAP_TO_NR_ENTRIES(order))
        order++;

    return order;
}

static inline ssize_t __parent(ssize_t idx) { return (idx - 1) / 2; }

static inline ssize_t __child(ssize_t idx) { return (2 * idx) + 1; }

static inline void __swap(void **a, void **b)
{
    void *tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

void Heap_Init(struct Heap *heap, int (*Compare)(const void *, const void *))
{
    Heap_InitNrEntries(heap, NR_ENTRIES_MIN, Compare);
}

void Heap_InitNrEntries(struct Heap *heap, size_t nr_ntries,
    int (*Compare)(const void *, const void *))
{
    heap->order = __toOrder(nr_ntries);
    heap->nr_entries = nr_ntries;
    heap->used = 0;
    heap->Compare = Compare;

    DPRINTF("nr_entries : %zu\n", heap->nr_entries);
}

void Heap_Insert(struct Heap *heap, void *entry)
{
    ssize_t pos = heap->used;
    ssize_t parent = __parent(pos);
    int diff;

    heap->entry[pos] = entry;

    while (pos > 0) {
        diff = heap->Compare(heap->entry[pos], heap->entry[parent]);
        if (diff >= 0)
            break;

        __swap(&(heap->entry[pos]), &(heap->entry[parent]));
        pos = parent;
        parent = __parent(pos);
    }

    heap->used++;
}

void *Heap_RemoveHead(struct Heap *heap)
{
    void **entry = heap->entry;
    ssize_t parent = 0;
    void *d;
    ssize_t left;
    ssize_t right;

    d = entry[0];
    __swap(&entry[0], &entry[--heap->used]);

    left = __child(0);
    right = left + 1;
    while (true) {
        ssize_t child = 0;

        if (left >= heap->used)
            break;

        if (right >= heap->used)
            child = left;
        else {
            if (heap->Compare(entry[left], entry[right]) > 0)
                child = right;
            else
                child = left;
        }

        if (heap->Compare(entry[child], entry[parent]) < 0) {
            __swap(&entry[parent], &entry[child]);
            parent = child;
        } else
            break;

        left = __child(parent);
        right = left + 1;
    }

    return d;
}

void Heap_Forward(
    struct Heap *heap, void (*Call)(void *, void *), void *private)
{
    size_t i;

    for (i = 0; i < heap->used; i++)
        Call(heap->entry[i], private);
};

bool Heap_IsEmpty(struct Heap *heap) { return !heap->used; }

static inline struct Heap *__expand(struct Heap *heap)
{
    heap->order++;
    heap->nr_entries = HEAP_TO_NR_ENTRIES(heap->order);

    return realloc(heap, HEAP_BYTES(heap->nr_entries));
}

static inline struct Heap *__shrink(struct Heap *heap)
{
    size_t order = __toOrder(heap->used) + 1;

    if (heap->order <= order)
        return heap;

    heap->order = order;
    heap->nr_entries = HEAP_TO_NR_ENTRIES(order);

    return realloc(heap, HEAP_BYTES(heap->nr_entries));
}

struct Heap *Heap_Resize(struct Heap *heap)
{
    size_t nr_entries_old = heap->nr_entries;

    heap = heap->used == nr_entries_old ? __expand(heap) : __shrink(heap);

#ifdef _DEBUG
    if (heap->nr_entries != nr_entries_old)
        DPRINTF("nr_entries : %zu -> %zu\n", nr_entries_old, heap->nr_entries);
#endif

    return heap;
}
