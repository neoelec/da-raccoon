// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024-2025 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"

static void __merge(void *base, size_t size,
                    int (*Compare)(const void *, const void *), ssize_t start,
                    ssize_t middle, ssize_t end)
{
    ssize_t left = start;
    ssize_t right = middle + 1;
    ssize_t idx = 0;
    void *dest = malloc((end - start + 1) * size);

    while (left <= middle && right <= end) {
        if (COMPARE(Compare, base, left, right, size) < 0) {
            memcpy(BASE(dest, idx, size), BASE(base, left, size), size);
            left++;
        } else {
            memcpy(BASE(dest, idx, size), BASE(base, right, size), size);
            right++;
        }

        idx++;
    }

    if (left <= middle)
        memcpy(BASE(dest, idx, size), BASE(base, left, size),
               (middle - left + 1) * size);

    if (right <= end)
        memcpy(BASE(dest, idx, size), BASE(base, right, size),
               (end - right + 1) * size);

    memcpy(BASE(base, start, size), dest, (end - start + 1) * size);

    free(dest);
}

static void __mergeSort(void *base, size_t size,
                        int (*Compare)(const void *, const void *),
                        ssize_t start, ssize_t end)
{
    ssize_t middle;

    if (end - start < 1)
        return;

    middle = (start + end) / 2;

    __mergeSort(base, size, Compare, start, middle);
    __mergeSort(base, size, Compare, middle + 1, end);

    __merge(base, size, Compare, start, middle, end);
}

void MergeSort(void *base, size_t nmemb, size_t size,
               int (*Compare)(const void *, const void *))
{
    __mergeSort((uint8_t *)base, size, Compare, 0, nmemb - 1);
}
