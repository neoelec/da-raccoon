// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Open Addressing Hash Table */
#ifndef __OHT_H__
#define __OHT_H__

#include <stddef.h>

#include "common.h"

struct OHT {
    size_t nr_buckets;
    size_t used;
    size_t (*KeyHash)(const struct OHT *, const void *);
    size_t (*StepHash)(const struct OHT *, const void *);
    void *bucket[0];
};

#define OHT_BYTES(nr_buckets) \
    (sizeof(struct OHT) + (nr_buckets) * (sizeof(struct OHT_Head *)))

#ifdef __cplusplus
extern "C" {
#endif

extern void OHT_Init(struct OHT *table, size_t nr_buckets,
                     size_t (*KeyHash)(const struct OHT *, const void *),
                     size_t (*StepHash)(const struct OHT *, const void *));
extern void OHT_Insert(struct OHT *table, void *entry);
extern void OHT_Remove(struct OHT *table, void *entry);
extern void *OHT_Get(const struct OHT *table, const void *key_node,
                     int (*Compare)(const void *, const void *));
extern struct OHT *OHT_Expand(struct OHT *table, size_t threshold);
extern struct OHT *OHT_Shrink(struct OHT *table, size_t threshold);
extern void OHT_Traverse(struct OHT *table, void (*Call)(void *, void *),
                         void *private);

#ifdef __cplusplus
}
#endif
#endif /* __OHT_H__ */
