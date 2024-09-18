// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static inline unsigned long __getMax(unsigned long *arr, size_t nmemb)
{
    unsigned long max = 0;
    size_t i;

    for (i = 0; i < nmemb; i++)
        max = max > arr[i] ? max : arr[i];

    return max;
}

static inline void __countSort(unsigned long *arr, size_t nmemb,
    unsigned long radix, unsigned long exp, unsigned long *output,
    unsigned long *count)
{
    ssize_t i;

    memset(count, 0, sizeof(*count) * radix);

    for (i = 0; i < nmemb; i++)
        count[(arr[i] / exp) % radix]++;

    for (i = 1; i < radix; i++)
        count[i] += count[i - 1];

    for (i = nmemb - 1; i >= 0; i--) {
        size_t idx = (arr[i] / exp) % radix;
        output[count[idx] - 1] = arr[i];
        count[idx]--;
    }

    memcpy(arr, output, sizeof(*arr) * nmemb);
}

void RadixSort(unsigned long *arr, size_t nmemb, unsigned long radix)
{
    unsigned long max = __getMax(arr, nmemb);
    unsigned long exp = 1;
    unsigned long *output = malloc(sizeof(*output) * nmemb);
    unsigned long *count = malloc(sizeof(*count) * radix);

    for (exp = 1; max / exp > 0; exp *= radix)
        __countSort(arr, nmemb, radix, exp, output, count);

    free(count);
    free(output);
}
