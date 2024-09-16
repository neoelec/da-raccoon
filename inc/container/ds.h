// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

/* Disjoint Set */
#ifndef __DS_H__
#define __DS_H__

#include <stddef.h>

#include "common.h"

struct DS_Head {
    struct DS_Head *parent;
};

#ifdef __cplusplus
extern "C" {
#endif

extern void DS_Union(struct DS_Head *set0, struct DS_Head *set1);
extern struct DS_Head *DS_Search(const struct DS_Head *set);

#ifdef __cplusplus
}
#endif
#endif /* __DS_H__ */
