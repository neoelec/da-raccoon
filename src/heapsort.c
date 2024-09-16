// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <sys/types.h>

#include <algorithm/heapsort.h>

static void __heapify(void **ptr_arr, size_t k, size_t r,
    int (*Compare)(const void *, const void *))
{
    size_t left = 2 * k + 1;
    size_t right = 2 * k + 2;
    size_t greater;
    void *tmp;

    if (right <= r) {
        if (Compare(ptr_arr[left], ptr_arr[right]) > 0)
            greater = left;
        else
            greater = right;
    } else if (left <= r)
        greater = left;
    else
        return;

    if (Compare(ptr_arr[greater], ptr_arr[k]) > 0) {
        tmp = ptr_arr[k];
        ptr_arr[k] = ptr_arr[greater];
        ptr_arr[greater] = tmp;
        __heapify(ptr_arr, greater, r, Compare);
    }
}

static inline void __buildHeap(
    void **ptr_arr, size_t r, int (*Compare)(const void *, const void *))
{
    ssize_t i;

    for (i = r / 2; i >= 0; i--)
        __heapify(ptr_arr, i, r, Compare);
}

void HeapSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    size_t i;
    void *tmp;

    __buildHeap(ptr_arr, nmemb - 1, Compare);

    for (i = nmemb - 1; i >= 1; i--) {
        tmp = ptr_arr[0];
        ptr_arr[0] = ptr_arr[i];
        ptr_arr[i] = tmp;
        __heapify(ptr_arr, 0, i - 1, Compare);
    }
}
