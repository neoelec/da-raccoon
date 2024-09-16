// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/cdll.h>

void CDLL_Init(struct CDLL *list) { list->head = NULL; }

void CDLL_InsertHead(struct CDLL *list, struct DLL_Node *node)
{
    if (list->head != NULL)
        DLL_InsertHead(list->head, node);
    else {
        DLL_Init(node);
        list->head = node;
    }
}

void CDLL_InsertTail(struct CDLL *list, struct DLL_Node *node)
{
    if (list->head != NULL)
        DLL_InsertTail(list->head, node);
    else {
        DLL_Init(node);
        list->head = node;
    }
}

void CDLL_Remove(struct CDLL *list, struct DLL_Node *node)
{
    if (node == list->head)
        list->head = node->next;

    DLL_Remove(node);

    if (list->head == node)
        list->head = NULL;
}

size_t CDLL_Count(const struct CDLL *list)
{
    if (list->head != NULL)
        return DLL_Count(list->head) + 1;

    return 0;
}

struct DLL_Node *CDLL_GetNode(const struct CDLL *list, ssize_t n)
{
    struct DLL_Node *node = list->head;

    if (node == NULL)
        return NULL;

    while ((--n) >= 0)
        node = node->next;

    return node;
}

void CDLL_Forward(
    struct CDLL *list, void (*Call)(struct DLL_Node *, void *), void *private)
{
    struct DLL_Node tmp_head;

    DLL_InsertBefore(list->head, &tmp_head);
    DLL_Forward(&tmp_head, Call, private);
    DLL_Remove(&tmp_head);
}

void CDLL_Reverse(
    struct CDLL *list, void (*Call)(struct DLL_Node *, void *), void *private)
{
    struct DLL_Node tmp_head;

    DLL_InsertBefore(list->head, &tmp_head);
    DLL_Reverse(&tmp_head, Call, private);
    DLL_Remove(&tmp_head);
}
