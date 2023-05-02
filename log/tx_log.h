#pragma once

#include <pthread.h>

struct tx_t {
    int tx_id;
    int client_id;
};
typedef struct tx_t tx_t;

struct tx_log_info_t {
    char filename[100];

    pthread_mutex_t ltid_mutex;
    int latest_tx_id;
};
typedef struct tx_log_info_t tx_log_info_t;

tx_log_info_t *tx_log_info_init(char *filename);
void tx_log_info_destroy(tx_log_info_t *tx_log_info);
void tx_log_append(tx_log_info_t *tx_log_info);
void tx_log_write(tx_log_info_t *tx_log_info, tx_t tx);
void tx_log_read(tx_log_info_t *tx_log_info, tx_t *tx, int tx_id);