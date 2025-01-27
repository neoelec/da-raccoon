// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024-2025 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"

static inline ssize_t __partition(void *base, size_t size,
                                  int (*Compare)(const void *, const void *),
                                  ssize_t left, ssize_t right)
{
    ssize_t first = left;
    void *pivot = BASE(base, first, size);

    ++left;
    while (left <= right) {
        while ((Compare(BASE(base, left, size), pivot) <= 0) && (left < right))
            ++left;

        while ((Compare(BASE(base, right, size), pivot) > 0) && (left <= right))
            --right;

        if (left < right)
            b_swap(base, left, right, size);
        else
            break;
    }

    b_swap(base, first, right, size);

    return right;
}

static void __quickSort(void *base, size_t size,
                        int (*Compare)(const void *, const void *),
                        ssize_t left, ssize_t right)
{
    if (left < right) {
        ssize_t index = __partition(base, size, Compare, left, right);

        __quickSort(base, size, Compare, left, index - 1);
        __quickSort(base, size, Compare, index + 1, right);
    }
}

void QuickSort(void *base, size_t nmemb, size_t size,
               int (*Compare)(const void *, const void *))
{
    __quickSort((uint8_t *)base, size, Compare, 0, nmemb - 1);
}
