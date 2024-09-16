// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Bubble Sort */
#ifndef __BOYERMOORE_H__
#define __BOYERMOORE_H__

#include <stddef.h>
#include <sys/types.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ssize_t BoyerMoore(const char *text, size_t text_len, size_t start,
    const char *pattern, size_t pattern_len);

#ifdef __cplusplus
}
#endif
#endif /* __BOYERMOORE_H__ */
