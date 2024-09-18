// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Radix Sort */
#ifndef __RADIXSORT_H__
#define __RADIXSORT_H__

#include <container/common.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void RadixSort(
    void *base, size_t nmemb, size_t size, unsigned long long order);
#ifdef __cplusplus
}
#endif
#endif /* __RADIXSORT_H__ */
