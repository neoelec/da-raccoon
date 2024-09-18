// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <algorithm/insertionsort.h>

static inline void __insertionSort(uint8_t *base, size_t nmemb, size_t size,
    int (*Compare)(const void *, const void *))
{
    size_t i;
    uint8_t tmp_static[16];
    uint8_t *new_item = (size > sizeof(tmp_static)) ? malloc(size) : tmp_static;

    for (i = 1; i < nmemb; i++) {
        ssize_t loc = i - 1;

        memcpy(new_item, &base[i * size], size);

        while (loc >= 0 && (Compare(new_item, base + loc * size) < 0)) {
            memcpy(&base[(loc + 1) * size], &base[loc * size], size);
            loc--;
        }

        memcpy(base + (loc + 1) * size, new_item, size);
    }

    if (size > sizeof(tmp_static))
        free(new_item);
}

void InsertionSort(void *base, size_t nmemb, size_t size,
    int (*Compare)(const void *, const void *))
{
    __insertionSort((uint8_t *)base, nmemb, size, Compare);
}
