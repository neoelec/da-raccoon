// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <container/ds.h>

void DS_Union(struct DS_Head *set0, struct DS_Head *set1)
{
    set1 = DS_Search(set1);
    set1->parent = set0;
}

struct DS_Head *DS_Search(const struct DS_Head *set)
{
    while (set->parent != NULL)
        set = set->parent;

    return (struct DS_Head *)set;
}
