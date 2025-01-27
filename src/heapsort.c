// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <sys/types.h>

#include <algorithm/heapsort.h>

#include "common.h"

static void __heapify(void *base, size_t k, size_t r, size_t size,
                      int (*Compare)(const void *, const void *))
{
    size_t left = 2 * k + 1;
    size_t right = 2 * k + 2;
    size_t greater;

    if (right <= r) {
        if (COMPARE(Compare, base, left, right, size) > 0)
            greater = left;
        else
            greater = right;
    } else if (left <= r)
        greater = left;
    else
        return;

    if (COMPARE(Compare, base, greater, k, size) > 0) {
        b_swap(base, k, greater, size);
        __heapify(base, greater, r, size, Compare);
    }
}

static inline void __buildHeap(void *base, size_t r, size_t size,
                               int (*Compare)(const void *, const void *))
{
    ssize_t i;

    for (i = r / 2; i >= 0; i--)
        __heapify(base, i, r, size, Compare);
}

void HeapSort(void *base, size_t nmemb, size_t size,
              int (*Compare)(const void *, const void *))
{
    size_t i;

    __buildHeap(base, nmemb - 1, size, Compare);

    for (i = nmemb - 1; i >= 1; i--) {
        b_swap(base, 0, i, size);
        __heapify(base, 0, i - 1, size, Compare);
    }
}
