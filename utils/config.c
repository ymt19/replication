#include "../utils/config.h"

#include <stdlib.h>

Config *create_config(double exp_time) {
    Config *config = malloc(sizeof(Config));
    config->finish_flag = 0;
    config->exp_time = exp_time;
}

int get_master_port(int slave_id) {
    return MASTER_PORT_OFFSET + slave_id;
}
int get_slave_port(int slave_id) {
    return SLAVE_PORT_OFFSET + slave_id;
}