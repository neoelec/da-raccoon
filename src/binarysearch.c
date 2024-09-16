// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>
#include <sys/types.h>

#include <algorithm/binarysearch.h>

void *BinarySearch(const void *key, void **ptr_arr, size_t nmemb,
    int (*Compare)(const void *, const void *))
{
    ssize_t left, right;

    left = 0;
    right = nmemb - 1;

    while (left <= right) {
        ssize_t mid = (left + right) / 2;
        int diff = Compare(key, ptr_arr[mid]);

        if (diff == 0)
            return ptr_arr[mid];
        else if (diff > 0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return NULL;
}
