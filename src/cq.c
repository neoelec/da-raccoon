// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <errno.h>

#include <container/cq.h>

static inline size_t __count(const struct CQ *queue)
{
    if (queue->front <= queue->rear)
        return queue->rear - queue->front;
    else
        return queue->rear + (queue->nr_entries - queue->front) + 1;
}

static inline bool __isEmpty(const struct CQ *queue)
{
    return queue->front == queue->rear;
}

static inline bool __isFull(const struct CQ *queue)
{
    return __count(queue) == queue->nr_entries;
}

void CQ_Init(struct CQ *queue, size_t nr_entries)
{
    queue->nr_entries = nr_entries;
    queue->front = 0;
    queue->rear = 0;
}

int CQ_Enqueue(struct CQ *queue, void *entry)
{
    size_t pos;

    if (__isFull(queue))
        return -EIO;

    if (queue->rear == queue->nr_entries)
        pos = queue->rear = 0;
    else
        pos = queue->rear++;

    queue->entry[pos] = entry;

    return 0;
}

void *CQ_Dequeue(struct CQ *queue)
{
    size_t pos;

    if (__isEmpty(queue))
        return NULL;

    if (queue->front == queue->nr_entries)
        pos = queue->front = 0;
    else
        pos = queue->front++;

    return queue->entry[pos];
}

size_t CQ_Count(const struct CQ *queue) { return __count(queue); }

bool CQ_IsEmpty(const struct CQ *queue) { return __isEmpty(queue); }

bool CQ_IsFull(const struct CQ *queue) { return __isFull(queue); }

void *CQ_Front(const struct CQ *queue)
{
    if (__isEmpty(queue))
        return NULL;

    return queue->entry[queue->front];
}

void *CQ_Rear(const struct CQ *queue)
{
    size_t i;

    if (__isEmpty(queue))
        return NULL;

    i = (queue->rear + queue->nr_entries - 1) % queue->nr_entries;
    return queue->entry[i];
}

void CQ_Forward(struct CQ *queue, void (*Call)(void *, void *), void *private)
{
    const size_t n = __count(queue);
    size_t i;

    for (i = 0; i < n; i++) {
        size_t j = (queue->front + i) % queue->nr_entries;
        Call(queue->entry[j], private);
    }
}
