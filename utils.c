#include "utils.h"

double now() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + .000001 * tv.tv_usec;
}

unsigned int fast_rand_seed;

int fast_rand() {
    fast_rand_seed = (214013 * fast_rand_seed + 2531011);
    return (fast_rand_seed >> 16) & 0x7FFF;
}
