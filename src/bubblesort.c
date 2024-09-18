// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <algorithm/bubblesort.h>

#include "common.h"

void BubbleSort(void *base, size_t nmemb, size_t size,
    int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb; i++) {
        size_t j;

        for (j = 0; j < nmemb - (i + 1); j++) {
            if (COMPARE(Compare, base, j, j + 1, size) > 0)
                b_swap(base, j, j + 1, size);
        }
    }
}
