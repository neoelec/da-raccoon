// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <algorithm/selectionsort.h>

#include "common.h"

void SelectionSort(void *base, size_t nmemb, size_t size,
                   int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb - 1; i++) {
        size_t j;
        size_t min = i;

        for (j = i + 1; j < nmemb; j++) {
            if (COMPARE(Compare, base, j, min, size) < 0)
                min = j;
        }

        b_swap(base, i, min, size);
    }
}
