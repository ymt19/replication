#pragma once

#include <pthread.h>

struct tx_log_info_t {
    char filename[100];

    pthread_mutex_t ltid_mutex;
    int latest_tx_id;               // 最新TXID（共有変数）
};
typedef struct tx_log_info_t tx_log_info_t;

tx_log_info_t *tx_log_info_init(char *filename);
void tx_log_info_destroy(tx_log_info_t *tx_log_info);
int tx_log_append(tx_log_info_t *tx_log_info);
int tx_log_get_ltid(tx_log_info_t *tx_log_info);