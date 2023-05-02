#include "../utils/config.h"

#include <stdlib.h>

config_t *master_config_init(double exp_time) {
    config_t *config = malloc(sizeof(config_t));
    config->finish_flag = 0;
    config->exp_time = exp_time;

    config->tx_log_info = tx_log_info_init("tx_log.csv");

    return config;
}

int get_master_port(int slave_id) {
    return MASTER_PORT_OFFSET + slave_id;
}
int get_slave_port(int slave_id) {
    return SLAVE_PORT_OFFSET + slave_id;
}