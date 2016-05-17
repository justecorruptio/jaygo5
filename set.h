#ifndef SET_H
#define SET_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _SET_BUCKET_SIZE 32
#define _SET_BUCKET_TYPE uint32_t

#define SetOf(max_size, type) \
    struct { \
        _SET_BUCKET_TYPE arr[ \
        (max_size + _SET_BUCKET_SIZE - 1) / _SET_BUCKET_SIZE]; \
    }

#define set_clear(set) \
    (bzero(set, sizeof(*(set))))

#define set_new(set_type) \
    (calloc(1, sizeof(set_type)))

inline int _set_add(void * set, uint64_t val) {
    ((_SET_BUCKET_TYPE *)set)[(val / _SET_BUCKET_SIZE)] |=
        (1 << (val % _SET_BUCKET_SIZE));
    return 1;
}

#define set_add(set, val) \
    _set_add((void *)set, val)

inline int _set_has(void * set, uint64_t val) {
    return !!(
        ((_SET_BUCKET_TYPE *)set)[(val / _SET_BUCKET_SIZE)] &
            (1 << (val % _SET_BUCKET_SIZE))
    );
}

#define set_has(set, val) \
    _set_has((void *)set, val)

#endif
