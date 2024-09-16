// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Linear Search */
#ifndef __LINEARSEARCH_H__
#define __LINEARSEARCH_H__

#include <stddef.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void *LinearSearch(const void *key, void **ptr_arr, size_t nmemb,
    int (*Compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif
#endif /* __LINEARSEARCH_H__ */
