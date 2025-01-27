// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024-2025 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <algorithm/shellsort.h>

#include "common.h"

static inline void __intervalSort(void *base, size_t size, ssize_t begin,
                                  ssize_t end, ssize_t intv,
                                  int (*Compare)(const void *, const void *))
{
    ssize_t i;
    uint8_t tmp_static[16];
    uint8_t *new_item = (size > sizeof(tmp_static)) ? malloc(size) : tmp_static;

    for (i = begin + intv; i <= end; i = i + intv) {
        ssize_t j;

        memcpy(new_item, BASE(base, i, size), size);

        j = i - intv;
        while (j >= begin) {
            if (Compare(new_item, BASE(base, j, size)) >= 0)
                break;

            memcpy(BASE(base, j + intv, size), BASE(base, j, size), size);
            j -= intv;
        }

        memcpy(BASE(base, j + intv, size), new_item, size);
    }

    if (size > sizeof(tmp_static))
        free(new_item);
}

void ShellSort(void *base, size_t nmemb, size_t size,
               int (*Compare)(const void *, const void *))
{
    size_t intv;
    size_t i;

    intv = nmemb / 2;
    while (intv >= 1) {
        for (i = 0; i < intv; i++)
            __intervalSort(base, size, i, nmemb - 1, intv, Compare);

        intv /= 2;
    }
}
