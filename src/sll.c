// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/sll.h>

void SLL_Init(struct SLL_Node *head)
{
    head->next = NULL;
}

void SLL_InsertTail(struct SLL_Node *head, struct SLL_Node *node)
{
    struct SLL_Node *prev = head;
    struct SLL_Node *next = head->next;

    while (next != NULL) {
        struct SLL_Node *tmp = prev;
        prev = next;
        next = tmp->next;
    }

    prev->next = node;
}

void SLL_InsertAfter(struct SLL_Node *pos, struct SLL_Node *node)
{
    node->next = pos->next;
    pos->next = node;
}

void SLL_Remove(struct SLL_Node *head, struct SLL_Node *node)
{
    struct SLL_Node *pos = head;

    while ((pos != NULL) && (pos->next != node))
        pos = pos->next;

    if (pos != NULL)
        pos->next = node->next;
}

size_t SLL_Count(const struct SLL_Node *head)
{
    struct SLL_Node *node = head->next;
    size_t count = 0;

    while (node != NULL) {
        count++;
        node = node->next;
    }

    return count;
}

struct SLL_Node *SLL_GetNode(const struct SLL_Node *head, ssize_t n)
{
    struct SLL_Node *node = head->next;

    while (node != NULL && (--n) >= 0)
        node = node->next;

    return node;
}

void SLL_Forward(struct SLL_Node *head, void (*Call)(struct SLL_Node *, void *),
                 void *private)
{
    struct SLL_Node *node = head->next;

    while (node) {
        struct SLL_Node *next = node->next;
        Call(node, private);
        node = next;
    }
}

void SLL_Reverse(struct SLL_Node *head)
{
    struct SLL_Node reverse;
    struct SLL_Node *node = head->next;

    SLL_Init(&reverse);

    while (node) {
        struct SLL_Node *next = node->next;
        SLL_InsertAfter(&reverse, node);
        node = next;
    }

    head->next = reverse.next;
}
