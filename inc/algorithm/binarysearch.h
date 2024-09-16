// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Binary Search */
#ifndef __BINARYSEARCH_H__
#define __BINARYSEARCH_H__

#include <stddef.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void *BinarySearch(const void *key, void **ptr_arr, size_t nmemb,
    int (*Compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif
#endif /* __BINARYSEARCH_H__ */
