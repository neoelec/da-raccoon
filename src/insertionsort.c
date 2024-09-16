// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <string.h>

#include <algorithm/insertionsort.h>

void InsertionSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    size_t i, j;

    for (i = 1; i < nmemb; i++) {
        void *v;

        if (Compare(ptr_arr[i - 1], ptr_arr[i]) <= 0)
            continue;

        v = ptr_arr[i];
        for (j = 0; j < i; j++) {
            if (Compare(ptr_arr[j], v) > 0) {
                memmove(&ptr_arr[j + 1], &ptr_arr[j], sizeof(void *) * (i - j));
                ptr_arr[j] = v;
                break;
            }
        }
    }
}
