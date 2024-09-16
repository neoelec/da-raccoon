// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>
#include <sys/types.h>

#include <algorithm/binarysearch.h>

void *LinearSearch(const void *key, void **ptr_arr, size_t nmemb,
    int (*Compare)(const void *, const void *))
{
    size_t i;

    for (i = 0; i < nmemb; i++) {
        void *v = ptr_arr[i];

        if (!Compare(key, v)) {
            DPRINTF("%zu번째에 검색 성공!\n", i);
            return v;
        }
    }

    return NULL;
}
