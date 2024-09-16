// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stddef.h>

#ifndef CONTAINER_OF
#define CONTAINER_OF(ptr, type, member)                                        \
    ((type *)(((char *)ptr) - offsetof(type, member)))
#endif

#ifndef NR_ELEM
#define NR_ELEM(a) ((sizeof(a)) / (sizeof((a)[0])))
#endif

#endif /* __COMMON_H__ */
