// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <algorithm/knuthmorrispratt.h>

static inline void __preprocess(
    const char *pattern, ssize_t pattern_len, ssize_t *border)
{
    ssize_t i = 0;
    ssize_t j = -1;

    border[0] = -1;

    while (i < pattern_len) {
        while (j > -1 && pattern[i] != pattern[j])
            j = border[j];

        i++;
        j++;

        border[i] = j;
    }
}

ssize_t KnuthMorrisPratt(const char *text, size_t text_len, size_t start,
    const char *pattern, size_t pattern_len)
{
    ssize_t i = start;
    ssize_t j = 0;
    ssize_t pos = -1;
    ssize_t *border = calloc(pattern_len + 1, sizeof(*border));

    __preprocess(pattern, pattern_len, border);

    while (i < text_len) {
        while (j >= 0 && text[i] != pattern[j])
            j = border[j];

        i++;
        j++;

        if (j == pattern_len) {
            pos = i - j;
            break;
        }
    }

    free(border);

    return pos;
}
