// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static inline unsigned long long __maskULL(size_t size)
{
    unsigned long long ull = 0;

    return (~ull) >> ((sizeof(ull) - (unsigned long long)size) * 8);
}

static inline unsigned long long __getMax(uint8_t *base, size_t nmemb,
                                          size_t size)
{
    unsigned long long mask_ull = __maskULL(size);
    unsigned long long max = 0;
    unsigned long long tmp;
    size_t i;

    for (i = 0; i < nmemb / size; i++) {
        tmp = *(unsigned long long *)&base[i * size] & mask_ull;
        max = max > tmp ? max : tmp;
    }

    return max;
}

static inline unsigned long long __toIdx(uint8_t *base, ssize_t i, size_t size,
                                         unsigned long long shift,
                                         unsigned long long mask_radix,
                                         unsigned long long mask_ull)
{
    unsigned long long tmp = *(unsigned long long *)&base[i * size] & mask_ull;

    return (tmp >> shift) & mask_radix;
}

static inline void __countSort(uint8_t *base, size_t nmemb, size_t size,
                               unsigned long long shift,
                               unsigned long long order,
                               unsigned long long *output,
                               unsigned long long *count)
{
    unsigned long long mask_ull = __maskULL(size);
    unsigned long long mask_radix = (1 << order) - 1;
    unsigned long long idx;
    ssize_t i;

    memset(count, 0, sizeof(*count) << order);

    for (i = 0; i < nmemb; i++) {
        idx = __toIdx(base, i, size, shift, mask_radix, mask_ull);
        count[idx]++;
    }

    for (i = 1; i <= mask_radix; i++)
        count[i] += count[i - 1];

    for (i = nmemb - 1; i >= 0; i--) {
        idx = __toIdx(base, i, size, shift, mask_radix, mask_ull);
        output[count[idx] - 1] = *(unsigned long long *)&base[i * size] &
                                 mask_ull;
        count[idx]--;
    }

    for (i = 0; i < nmemb; i++)
        memcpy(&base[i * size], &output[i], size);
}

static inline void __radixSort(uint8_t *base, size_t nmemb, size_t size,
                               unsigned long long order)
{
    unsigned long long max = __getMax(base, nmemb, size);
    unsigned long long *output = malloc(sizeof(*output) * nmemb);
    unsigned long long *count = malloc(sizeof(*count) << order);
    unsigned long long shift;

    for (shift = 0; (max >> shift) > 0; shift += order)
        __countSort(base, nmemb, size, shift, order, output, count);

    free(count);
    free(output);
}

void RadixSort(void *base, size_t nmemb, size_t size, unsigned long long order)
{
    assert(size <= sizeof(unsigned long long));
    assert(order > 0);

    __radixSort((uint8_t *)base, nmemb, size, order);
}
