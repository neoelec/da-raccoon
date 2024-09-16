// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <container/dll.h>

void DLL_Init(struct DLL_Node *head)
{
    head->prev = head;
    head->next = head;
}

void DLL_InsertHead(struct DLL_Node *head, struct DLL_Node *node)
{
    DLL_InsertAfter(head, node);
}

void DLL_InsertTail(struct DLL_Node *head, struct DLL_Node *node)
{
    DLL_InsertBefore(head, node);
}

void DLL_Remove(struct DLL_Node *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
}

size_t DLL_Count(const struct DLL_Node *head)
{
    struct DLL_Node *node = head->next;
    size_t count = 0;

    while (node != head) {
        count++;
        node = node->next;
    }

    return count;
}

struct DLL_Node *DLL_GetNode(const struct DLL_Node *head, ssize_t n)
{
    struct DLL_Node *node = head->next;

    while (node != head && (--n) >= 0)
        node = node->next;

    return node;
}

void DLL_Forward(struct DLL_Node *head, void (*Call)(struct DLL_Node *, void *),
    void *private)
{
    struct DLL_Node *node = head->next;

    while (node != head) {
        Call(node, private);
        node = node->next;
    }
}

void DLL_Reverse(struct DLL_Node *head, void (*Call)(struct DLL_Node *, void *),
    void *private)
{
    struct DLL_Node *node = head->prev;

    while (node != head) {
        Call(node, private);
        node = node->prev;
    }
}
