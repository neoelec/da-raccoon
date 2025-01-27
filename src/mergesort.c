// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024-2025 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "common.h"

static inline void __memcpy(void *dest, size_t d_idx, const void *base,
                            size_t b_idx, size_t size)
{
    memcpy(BASE(dest, d_idx, size), BASE(base, b_idx, size), size);
}

void MergeSort(void *base, size_t nmemb, size_t size,
               int (*Compare)(const void *, const void *))
{
    size_t idx;
    void *dest = malloc(size * nmemb);

    for (idx = 1; idx < nmemb; idx <<= 1) {
        size_t first = -2 * idx;
        size_t second = first + idx;

        while (second + idx * 2 < nmemb) {
            size_t i, j, k;

            i = k = first = second + idx;
            j = second = first + idx;

            while (i < first + idx || (j < second + idx && j < nmemb)) {
                if (COMPARE(Compare, base, i, j, size) <= 0) {
                    if (i < first + idx)
                        __memcpy(dest, k++, base, i++, size);
                    else
                        __memcpy(dest, k++, base, j++, size);
                } else {
                    if (j < second + idx && j < nmemb)
                        __memcpy(dest, k++, base, j++, size);
                    else
                        __memcpy(dest, k++, base, i++, size);
                }
            }
        }

        memcpy(base, dest, nmemb * size);
    }

    free(dest);
}
