// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Chaining Hash Table */
#ifndef __CHT_H__
#define __CHT_H__

#include <stddef.h>

#include "common.h"
#include "dll.h"

struct CHT {
    size_t nr_buckets;
    size_t (*KeyHash)(const struct CHT *, const struct DLL_Node *);
    struct DLL_Node bucket[0];
};

#define CHT_BYTES(nr_buckets)                                                  \
    (sizeof(struct CHT) + (nr_buckets) * (sizeof(struct DLL_Node)))

#ifdef __cplusplus
extern "C" {
#endif

extern void CHT_Init(struct CHT *table, size_t nr_buckets,
    size_t (*KeyHash)(const struct CHT *, const struct DLL_Node *));
extern void CHT_Insert(struct CHT *table, struct DLL_Node *node);
extern void CHT_Remove(struct CHT *table, struct DLL_Node *node);
extern struct DLL_Node *CHT_Get(struct CHT *table,
    const struct DLL_Node *key_node,
    int (*Compare)(const struct DLL_Node *, const struct DLL_Node *));
extern void CHT_Traverse(
    struct CHT *table, void (*Call)(struct DLL_Node *, void *), void *private);

#ifdef __cplusplus
}
#endif
#endif /* __CHT_H__ */
