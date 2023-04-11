#pragma once

#define LOCAL_IPADDR        "127.0.0.1"
#define MASTER_PORT_OFFSET   5000
#define SLAVE_PORT_OFFSET   6000

struct Config {
    int finish_flag;
    double exp_time;
    double start_time;
};
typedef struct Config Config;

Config *create_config(double exp_time);
int get_master_port();
int get_slave_port(int);