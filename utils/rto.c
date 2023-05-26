#include <math.h>

#include "../utils/rto.h"
#include "../utils/timer.h"

int check_rto(double first_sent_time, int transmission_cnt) {
    double rto = RTO_MIN * (pow(2,transmission_cnt) - 1) / (2 - 1);

    if (get_time() - first_sent_time >= rto) {
        return 1;
    } else {
        return 0;
    }
}