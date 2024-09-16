// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/sht.h>

void SHT_Init(struct SHT *table, size_t nr_buckets,
    size_t (*KeyHash)(const struct SHT *, const void *))
{
    size_t i;

    table->KeyHash = KeyHash;

    table->nr_buckets = nr_buckets;
    for (i = 0; i < nr_buckets; i++)
        table->bucket[i] = NULL;
}

static inline void *__set(struct SHT *table, size_t key, void *entry)
{
    void *old = table->bucket[key];

    if (key >= table->nr_buckets)
        return NULL;

    table->bucket[key] = entry;

    return old;
}

void *SHT_Insert(struct SHT *table, void *entry)
{
    size_t key = table->KeyHash(table, entry);

    return __set(table, key, entry);
}

void *SHT_Remove(struct SHT *table, void *entry)
{
    size_t key = table->KeyHash(table, entry);

    return __set(table, key, NULL);
}

void *SHT_Get(const struct SHT *table, void *key_entry)
{
    size_t key = table->KeyHash(table, key_entry);

    return table->bucket[key];
}

void SHT_Traverse(
    struct SHT *table, void (*Call)(void *, void *), void *private)
{
    size_t i;

    for (i = 0; i < table->nr_buckets; i++) {
        if (table->bucket[i] != NULL)
            Call(table->bucket[i], private);
    }
}
