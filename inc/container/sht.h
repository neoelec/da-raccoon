// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Simple Hash Table */
#ifndef __SHT_H__
#define __SHT_H__

#include <stddef.h>

#include "common.h"

struct SHT {
    size_t nr_buckets;
    size_t (*KeyHash)(const struct SHT *, const void *);
    void *bucket[0];
};

#define SHT_BYTES(nr_buckets) \
    (sizeof(struct SHT) + (nr_buckets) * (sizeof(void *)))

#ifdef __cplusplus
extern "C" {
#endif

extern void SHT_Init(struct SHT *table, size_t nr_buckets,
                     size_t (*KeyHash)(const struct SHT *, const void *));
extern void *SHT_Insert(struct SHT *table, void *entry);
extern void *SHT_Remove(struct SHT *table, void *entry);
extern void *SHT_Get(const struct SHT *table, void *key_entry);
extern void SHT_Traverse(struct SHT *table, void (*Call)(void *, void *),
                         void *private);

#ifdef __cplusplus
}
#endif
#endif /* __SHT_H__ */
