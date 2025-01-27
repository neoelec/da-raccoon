// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <algorithm/bruteforcesearch.h>

ssize_t BruteForceSearch(const char *text, size_t text_len, size_t start,
                         const char *pattern, size_t pattern_len)
{
    ssize_t i;

    for (i = start; i <= text_len - pattern_len; i++) {
        ssize_t j;

        for (j = 0; j < pattern_len; j++)
            if (text[i + j] != pattern[j])
                break;

        if (j >= pattern_len)
            return i;
    }

    return -1;
}
