// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/cht.h>

void CHT_Init(struct CHT *table, size_t nr_buckets,
    size_t (*KeyHash)(const struct CHT *, const struct DLL_Node *))
{
    struct DLL_Node *bucket = table->bucket;
    size_t i;

    table->KeyHash = KeyHash;

    table->nr_buckets = nr_buckets;
    for (i = 0; i < nr_buckets; i++)
        DLL_Init(&bucket[i]);
}

void CHT_Insert(struct CHT *table, struct DLL_Node *node)
{
    struct DLL_Node *head;
    size_t addr;

    addr = table->KeyHash(table, node);
    head = &table->bucket[addr];

    if (head != head->next)
        DPRINTF("Collision occured! : at. %p, Address(%zu)\n  -> ", node, addr);

    DPRINTF("%p entered at address (%zu)\n", node, addr);
    DLL_InsertTail(head, node);
}

void CHT_Remove(struct CHT *table, struct DLL_Node *node) { DLL_Remove(node); }

static struct DLL_Node *__getHead(
    struct CHT *table, const struct DLL_Node *key_node)
{
    size_t hash;

    hash = table->KeyHash(table, key_node);
    if (hash > table->nr_buckets)
        return NULL;

    return &table->bucket[hash];
}

struct DLL_Node *CHT_Get(struct CHT *table, const struct DLL_Node *key_node,
    int (*Compare)(const struct DLL_Node *, const struct DLL_Node *))
{
    struct DLL_Node *head = __getHead(table, key_node);
    struct DLL_Node *node;

    if (head == NULL)
        return NULL;

    for (node = head->next; node != head; node = node->next) {
        if (!Compare(node, key_node))
            return node;
    }

    return NULL;
}

void CHT_Traverse(
    struct CHT *table, void (*Call)(struct DLL_Node *, void *), void *private)
{
    size_t i;

    for (i = 0; i < table->nr_buckets; i++)
        DLL_Forward(&table->bucket[i], Call, private);
}
