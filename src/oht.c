// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/oht.h>

void OHT_Init(struct OHT *table, size_t nr_buckets,
    size_t (*KeyHash)(const struct OHT *, const void *),
    size_t (*StepHash)(const struct OHT *, const void *))
{
    size_t i;

    table->KeyHash = KeyHash;
    table->StepHash = StepHash;

    table->nr_buckets = nr_buckets;
    for (i = 0; i < nr_buckets; i++)
        table->bucket[i] = NULL;
}

static size_t __insert(struct OHT *table, void *entry)
{
    size_t addr, step_size;
    void **bucket = table->bucket;

    step_size = table->StepHash(table, entry);
    addr = table->KeyHash(table, entry);
    while (bucket[addr] != NULL) {
        DPRINTF("Collision occured! : vs. %p, Address(%zu)\n  -> ",
            bucket[addr], addr);
        addr = (addr + step_size) % table->nr_buckets;
    }

    bucket[addr] = entry;
    table->used++;

    return addr;
}

void OHT_Insert(struct OHT *table, void *entry)
{
    size_t addr = __insert(table, entry);

    addr = addr;

    DPRINTF("%p entered at address (%zu)\n", entry, addr);
}

void OHT_Remove(struct OHT *table, void *entry)
{
    size_t addr, step_size;
    void **bucket = table->bucket;

    step_size = table->StepHash(table, entry);
    addr = table->KeyHash(table, entry);
    while (bucket[addr] != entry)
        addr = (addr + step_size) % table->nr_buckets;

    bucket[addr] = NULL;
    table->used--;
}

void *OHT_Get(const struct OHT *table, const void *key_entry,
    int (*Compare)(const void *, const void *))
{
    size_t addr, addr_1st;
    size_t step_size;
    void *const *bucket = table->bucket;

    step_size = table->StepHash(table, key_entry);
    addr_1st = table->KeyHash(table, key_entry);
    addr = addr_1st;
    while (bucket[addr] != NULL) {
        if (!Compare(bucket[addr], key_entry))
            return bucket[addr];

        addr = (addr + step_size) % table->nr_buckets;
        if (addr == addr_1st)
            break;
    }

    return NULL;
}

static inline size_t __usageRate(struct OHT *table)
{
    return (table->used * 100) / table->nr_buckets;
}

static void __copy(struct OHT *new_tbl, const struct OHT *old_tbl)
{
    size_t i;

    for (i = 0; i < old_tbl->nr_buckets; i++) {
        if (old_tbl->bucket[i] == NULL)
            continue;

        __insert(new_tbl, old_tbl->bucket[i]);
    }
}

static struct OHT *__rehash(struct OHT *table, size_t nr_buckets)
{
    struct OHT *new_tbl;

    new_tbl = malloc(OHT_BYTES(nr_buckets));

    OHT_Init(new_tbl, nr_buckets, table->KeyHash, table->StepHash);
    __copy(new_tbl, table);

    free(table);

    return new_tbl;
}

struct OHT *OHT_Expand(struct OHT *table, size_t threshold)
{
    if (__usageRate(table) <= threshold)
        return table;

    return __rehash(table, table->nr_buckets * 2);
}

struct OHT *OHT_Shrink(struct OHT *table, size_t threshold)
{
    if (__usageRate(table) > threshold)
        return table;

    return __rehash(table, table->nr_buckets / 2);
}

void OHT_Traverse(
    struct OHT *table, void (*Call)(void *, void *), void *private)
{
    size_t i;

    for (i = 0; i < table->nr_buckets; i++) {
        if (table->bucket[i] != NULL)
            Call(table->bucket[i], private);
    }
}
