// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Circular Queue */
#ifndef __CQ_H__
#define __CQ_H__

#include <stdbool.h>
#include <stddef.h>

#include "common.h"

struct CQ {
    size_t nr_entries;
    size_t front;
    size_t rear;
    void *entry[0];
};

#define CQ_BYTES(nr_entries) \
    (sizeof(struct CQ) + (nr_entries) * (sizeof(void *)))

#ifdef __cplusplus
extern "C" {
#endif

extern void CQ_Init(struct CQ *stack, size_t nr_entries);
extern int CQ_Enqueue(struct CQ *queue, void *x);
extern void *CQ_Dequeue(struct CQ *queue);
extern size_t CQ_Count(const struct CQ *queue);
extern bool CQ_IsEmpty(const struct CQ *queue);
extern bool CQ_IsFull(const struct CQ *queue);
extern void *CQ_Front(const struct CQ *queue);
extern void *CQ_Rear(const struct CQ *queue);
extern void CQ_Forward(struct CQ *queue, void (*Call)(void *, void *),
                       void *private);

#ifdef __cplusplus
}
#endif
#endif /* __CQ_H__ */
