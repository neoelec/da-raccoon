// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdbool.h>
#include <string.h>
#include <sys/types.h>

#include <algorithm/shellsort.h>

static inline void __intervalSort(void **ptr_arr, ssize_t begin, ssize_t end,
    ssize_t intv, int (*Compare)(const void *, const void *))
{
    ssize_t i;

    for (i = begin + intv; i <= end; i = i + intv) {
        ssize_t j;
        void *item = ptr_arr[i];

        j = i - intv;
        while (j >= begin) {
            int diff = Compare(item, ptr_arr[j]);
            if (diff >= 0)
                break;

            ptr_arr[j + intv] = ptr_arr[j];
            j -= intv;
        }

        ptr_arr[j + intv] = item;
    }
}

void ShellSort(
    void **ptr_arr, size_t nmemb, int (*Compare)(const void *, const void *))
{
    size_t intv;
    size_t i;

    intv = nmemb / 2;
    while (intv >= 1) {
        for (i = 0; i < intv; i++)
            __intervalSort(ptr_arr, i, nmemb - 1, intv, Compare);

        intv /= 2;
    }
}
