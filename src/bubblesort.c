// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <algorithm/bubblesort.h>

void BubbleSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb; i++) {
        size_t j;

        for (j = 0; j < nmemb - (i + 1); j++) {
            if (Compare(ptr_arr[j], ptr_arr[j + 1]) > 0) {
                void *tmp = ptr_arr[j];
                ptr_arr[j] = ptr_arr[j + 1];
                ptr_arr[j + 1] = tmp;
            }
        }
    }
}
