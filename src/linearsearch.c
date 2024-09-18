// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>
#include <sys/types.h>

#include <algorithm/binarysearch.h>

void *LinearSearch(const void *key, void *base, size_t nmemb, size_t size,
    int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb; i++) {
        void *v = base + i * size;

        if (!Compare(key, v))
            return v;
    }

    return NULL;
}
