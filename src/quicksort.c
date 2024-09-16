// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <string.h>
#include <sys/types.h>

static inline ssize_t __partition(void **ptr_arr,
    int (*Compare)(const void *, const void *), ssize_t left, ssize_t right)
{
    ssize_t first = left;
    void *pivot = ptr_arr[first];
    void *tmp;

    ++left;
    while (left <= right) {
        while ((Compare(ptr_arr[left], pivot) <= 0) && (left < right))
            ++left;

        while ((Compare(ptr_arr[right], pivot) > 0) && (left <= right))
            --right;

        if (left < right) {
            tmp = ptr_arr[left];
            ptr_arr[left] = ptr_arr[right];
            ptr_arr[right] = tmp;
        } else
            break;
    }

    tmp = ptr_arr[first];
    ptr_arr[first] = ptr_arr[right];
    ptr_arr[right] = tmp;

    return right;
}

static void __quickSort(void **ptr_arr,
    int (*Compare)(const void *, const void *), ssize_t left, ssize_t right)
{
    if (left < right) {
        ssize_t index = __partition(ptr_arr, Compare, left, right);

        __quickSort(ptr_arr, Compare, left, index - 1);
        __quickSort(ptr_arr, Compare, index + 1, right);
    }
}

void QuickSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    __quickSort(ptr_arr, Compare, 0, nmemb - 1);
}
