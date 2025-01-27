// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <stdlib.h>

#include <algorithm/boyermoore.h>

#include "common.h"

#define ALPHABET_LEN 256

static inline void __buildBCT(const char *pattern, ssize_t pattern_len,
                              ssize_t *BCT)
{
    ssize_t i, j;

    for (i = 0; i < ALPHABET_LEN; i++)
        BCT[i] = -1;

    for (j = 0; j < pattern_len; j++)
        BCT[(size_t)pattern[j]] = j;
}

static inline void __buildGST(const char *pattern, ssize_t pattern_len,
                              ssize_t *suffix, ssize_t *GST)
{
    /* Case 1 */
    ssize_t i = pattern_len;
    ssize_t j = pattern_len + 1;

    suffix[i] = j;

    while (i > 0) {
        while (j <= pattern_len && pattern[i - 1] != pattern[j - 1]) {
            if (GST[j] == 0)
                GST[j] = j - i;

            j = suffix[j];
        }

        i--;
        j--;

        suffix[i] = j;
    }

    /* Case 2 */
    j = suffix[0];

    for (i = 0; i <= pattern_len; i++) {
        if (GST[i] == 0)
            GST[i] = j;

        if (i == j)
            j = suffix[j];
    }
}

ssize_t BoyerMoore(const char *text, size_t text_len, size_t start,
                   const char *pattern, size_t pattern_len)
{
    ssize_t BCT[ALPHABET_LEN];
    ssize_t *suffix = calloc(pattern_len + 1, sizeof(*suffix));
    ssize_t *GST = calloc(pattern_len + 1, sizeof(*GST));
    ssize_t i = start;
    ssize_t pos = -1;

    __buildBCT(pattern, pattern_len, BCT);
    __buildGST(pattern, pattern_len, suffix, GST);

    while (i <= text_len - pattern_len) {
        ssize_t j = pattern_len - 1;

        while (j >= 0 && pattern[j] == text[i + j])
            j--;

        if (j < 0) {
            pos = i;
            break;
        } else {
            i += MAX(GST[j + 1], j - BCT[(size_t)text[i + j]]);
        }
    }

    free(suffix);
    free(GST);

    return pos;
}
