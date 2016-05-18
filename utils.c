#include "utils.h"

double now() {
    struct timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec + .000001 * tv.tv_usec;
}
