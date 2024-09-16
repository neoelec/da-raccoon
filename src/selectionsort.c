// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <algorithm/selectionsort.h>

void SelectionSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb - 1; i++) {
        size_t j;
        size_t min = i;
        void *tmp;

        for (j = i + 1; j < nmemb; j++) {
            int diff = Compare(ptr_arr[j], ptr_arr[min]);
            if (diff < 0)
                min = j;
        }

        tmp = ptr_arr[i];
        ptr_arr[i] = ptr_arr[min];
        ptr_arr[min] = tmp;
    }
}
