#include "../utils/config.h"

#include <stdlib.h>
#include <pthread.h>

config_t *config_init(double exp_time, char *tx_log_filename) {
    config_t *config = malloc(sizeof(config_t));
    config->finish_flag = 0;
    pthread_mutex_init(&config->finish_flag_mutex, NULL);
    config->exp_time = exp_time;
    for (int id = 0; id < SLAVE_NODE_NUM; id++) {
        config->sent_lsn[id] = MIN_LSN - 1;
        pthread_mutex_init(&config->slsn_mutex[id], NULL);
    }

    config->tx_log_info = tx_log_info_init(tx_log_filename);

    return config;
}

void config_destroy(config_t *config) {
    pthread_mutex_destroy(&config->finish_flag_mutex);
    for (int slave_id = 0; slave_id < SLAVE_NODE_NUM; slave_id++) {
        pthread_mutex_destroy(&config->slsn_mutex[slave_id]);
    }
    tx_log_info_destroy(config->tx_log_info);
    free(config);
}

int config_get_finish_flag(config_t *config) {
    int ret;
    pthread_mutex_lock(&config->finish_flag_mutex);
    ret = config->finish_flag;
    pthread_mutex_unlock(&config->finish_flag_mutex);
    return ret;
}

void config_raise_finish_flag(config_t *config) {
    pthread_mutex_lock(&config->finish_flag_mutex);
    config->finish_flag = 1;
    pthread_mutex_unlock(&config->finish_flag_mutex);
}

int config_get_sent_lsn(config_t *config, int slave_id) {
    int ret;
    pthread_mutex_lock(&config->slsn_mutex[slave_id]);
    ret = config->sent_lsn[slave_id];
    pthread_mutex_unlock(&config->slsn_mutex[slave_id]);
    return ret;
}

void config_set_sent_lsn(config_t *config, int slave_id, int new_val) {
    pthread_mutex_lock(&config->slsn_mutex[slave_id]);
    config->sent_lsn[slave_id] = new_val;
    pthread_mutex_unlock(&config->slsn_mutex[slave_id]);
}

int get_master_port(int slave_id) {
    return MASTER_PORT_OFFSET + slave_id;
}
int get_slave_port(int slave_id) {
    return SLAVE_PORT_OFFSET + slave_id;
}