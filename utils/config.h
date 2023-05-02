#pragma once

#include "../log/tx_log.h"

#define LOCAL_IPADDR        "127.0.0.1"
#define MASTER_PORT_OFFSET   5000
#define SLAVE_PORT_OFFSET   6000

#define FILENAME_SIZE       32

struct config_t {
    int finish_flag;
    double exp_time;
    double start_time;

    tx_log_info_t *tx_log_info;
};
typedef struct config_t config_t;

config_t *master_config_init(double exp_time);
int get_master_port();
int get_slave_port(int);