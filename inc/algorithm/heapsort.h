// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Heap Sort */
#ifndef __HEAPSORT_H__
#define __HEAPSORT_H__

#include <stddef.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void HeapSort(void *base, size_t nmemb, size_t size,
                     int (*Compare)(const void *, const void *));

#ifdef __cplusplus
}
#endif
#endif /* __HEAPSORT_H__ */
