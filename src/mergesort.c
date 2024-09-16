// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>
#include <sys/types.h>

static void __merge(void **ptr_arr, int (*Compare)(const void *, const void *),
    ssize_t start, ssize_t middle, ssize_t end)
{
    ssize_t i;
    ssize_t left = start;
    ssize_t right = middle + 1;
    ssize_t idx = 0;

    void **dest = malloc(sizeof(void *) * (end - start + 1));

    while (left <= middle && right <= end) {
        if (Compare(ptr_arr[left], ptr_arr[right]) < 0) {
            dest[idx] = ptr_arr[left];
            left++;
        } else {
            dest[idx] = ptr_arr[right];
            right++;
        }

        idx++;
    }

    while (left <= middle)
        dest[idx++] = ptr_arr[left++];

    while (right <= end)
        dest[idx++] = ptr_arr[right++];

    idx = 0;
    for (i = start; i <= end; i++)
        ptr_arr[i] = dest[idx++];

    free(dest);
}

static void __mergeSort(void **ptr_arr,
    int (*Compare)(const void *, const void *), ssize_t start, ssize_t end)
{
    ssize_t middle;

    if (end - start < 1)
        return;

    middle = (start + end) / 2;

    __mergeSort(ptr_arr, Compare, start, middle);
    __mergeSort(ptr_arr, Compare, middle + 1, end);

    __merge(ptr_arr, Compare, start, middle, end);
}

void MergeSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    __mergeSort(ptr_arr, Compare, 0, nmemb - 1);
}
