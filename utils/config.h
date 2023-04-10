#pragma once

#define LOCAL_IPADDR        "127.0.0.1"
#define MASTER_PORT_OFFSET   5000
#define SLAVE_PORT_OFFSET   6000

struct Config {
    int finish_flag;
};
typedef struct Config Config;

int get_master_port();
int get_slave_port(int);