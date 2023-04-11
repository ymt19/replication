#include <stdio.h>
#include <sys/time.h>

#include "../utils/timer.h"

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec/1e6;
}