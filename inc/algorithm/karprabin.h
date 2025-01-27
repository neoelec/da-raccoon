// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Karp Rabin */
#ifndef __KARPRABIN_H__
#define __KARPRABIN_H__

#include <stddef.h>
#include <sys/types.h>

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ssize_t KarpRabin(const char *text, size_t text_len, size_t start,
                         const char *pattern, size_t pattern_len);

#ifdef __cplusplus
}
#endif
#endif /* __KARPRABIN_H__ */
