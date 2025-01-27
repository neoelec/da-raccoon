// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include <algorithm/binarysearch.h>

static inline void *__linearSearch(const void *key, const uint8_t *base,
                                   size_t nmemb, size_t size,
                                   int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb; i++) {
        const uint8_t *v = &base[i * size];

        if (!Compare(key, v))
            return (void *)v;
    }

    return NULL;
}

void *LinearSearch(const void *key, const void *base, size_t nmemb, size_t size,
                   int (*Compare)(const void *, const void *))
{
    return __linearSearch(key, (const uint8_t *)base, nmemb, size, Compare);
}
