// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024-2025 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#include <algorithm/binarysearch.h>

#include "common.h"

void *LinearSearch(const void *key, const void *base, size_t nmemb, size_t size,
                   int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb; i++) {
        const uint8_t *v = BASE(base, i, size);

        if (!Compare(key, v))
            return (void *)v;
    }

    return NULL;
}
