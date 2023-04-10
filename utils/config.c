#include "../utils/config.h"

int get_master_port(int slave_id) {
    return MASTER_PORT_OFFSET + slave_id;
}
int get_slave_port(int slave_id) {
    return SLAVE_PORT_OFFSET + slave_id;
}