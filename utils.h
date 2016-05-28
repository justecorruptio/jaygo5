#ifndef UTILS_H
#define UTILS_H

#include <sys/time.h>

#define nil (-1)

#define LOOP(var, end) \
    for(var = 0; (var) < (end); (var) ++)

#define ITER(var, ptr, start) \
    for(ptr = (start); (var = *(ptr)) != nil; (ptr) ++)

double now();
int fast_rand();

#endif
