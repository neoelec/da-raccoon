#ifndef __SRC_INTERNAL__COMMON_H__
#define __SRC_INTERNAL__COMMON_H__

#include <stddef.h>
#include <stdint.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define COMPARE(func, base, off_a, off_b, size)                                \
    func((base) + ((off_a) * (size)), (base) + ((off_b) * (size)))

static inline void b_swap(
    void *base, size_t off_a, size_t off_b, size_t size)
{
    uint8_t *a = (uint8_t *)(base + off_a * size);
    uint8_t *b = (uint8_t *)(base + off_b * size);
    uint8_t tmp;
    size_t i;

    for (i = 0; i < size; i++, a++, b++) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

#endif /* __SRC_INTERNAL__COMMON_H__ */
