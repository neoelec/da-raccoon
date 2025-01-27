// SPDX-License-Identifier: GPL-2.0+
// Copyright (c) 2024 YOUNGJIN JOO (neoelec@gmail.com)

#include <algorithm/karprabin.h>

static inline size_t __hash(const char *string, size_t len)
{
    size_t i;
    size_t hash_value = 0;

    for (i = 0; i < len; i++)
        hash_value += string[i] * (1 << (len - (1 + i)));

    return hash_value;
}

static inline size_t __reHash(const char *string, int len, int start,
                              int hash_prev, int coefficient)
{
    if (start == 0)
        return hash_prev;

    return ((hash_prev - coefficient * string[start - 1]) * 2) +
           string[start + len - 1];
}

ssize_t KarpRabin(const char *text, size_t text_len, size_t start,
                  const char *pattern, size_t pattern_len)
{
    size_t i;
    size_t coefficient = 1 << (pattern_len - 1);
    size_t hash_text = __hash(text, pattern_len);
    size_t hash_pattern = __hash(pattern, pattern_len);

    for (i = start; i <= text_len - pattern_len; i++) {
        hash_text = __reHash(text, pattern_len, i, hash_text, coefficient);

        if (hash_pattern == hash_text) {
            ssize_t j;
            for (j = 0; j < pattern_len; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }

            if (j >= pattern_len)
                return i;
        }
    }

    return -1;
}
