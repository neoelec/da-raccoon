// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include <algorithm/binarysearch.h>

static inline void *__binarySearch(const void *key, const uint8_t *base,
    size_t nmemb, size_t size, int (*Compare)(const void *, const void *))
{
    ssize_t left, right;

    left = 0;
    right = nmemb - 1;

    while (left <= right) {
        ssize_t mid = (left + right) / 2;
        int diff = Compare(key, &base[mid * size]);

        if (diff == 0)
            return (void *)&base[mid * size];
        else if (diff > 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return NULL;
}

void *BinarySearch(const void *key, const void *base, size_t nmemb, size_t size,
    int (*Compare)(const void *, const void *))
{
    return __binarySearch(key, (const uint8_t *)base, nmemb, size, Compare);
}
