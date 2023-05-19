#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../log/tx_log.h"
#include "../utils/config.h"

tx_log_info_t *tx_log_info_init(char *filename) {
    tx_log_info_t *tx_log_info;

    tx_log_info = malloc(sizeof(tx_log_info_t));
    
    strcpy(tx_log_info->filename, filename);
    pthread_mutex_init(&tx_log_info->ltid_mutex, NULL);
    tx_log_info->latest_tx_id = MIN_LSN - 1;

    // ファイル削除
    remove(tx_log_info->filename);

    return tx_log_info;
}

void tx_log_info_destroy(tx_log_info_t *tx_log_info) {
    pthread_mutex_destroy(&tx_log_info->ltid_mutex);
    free(tx_log_info);
}

/**
 * @brief 
 * 
 * @return int 作成したtxのid 
 */
int tx_log_append(tx_log_info_t *tx_log_info) {
    int new_tx_id;
    pthread_mutex_lock(&tx_log_info->ltid_mutex);
    tx_log_info->latest_tx_id++;
    printf("add txid:%d\n", tx_log_info->latest_tx_id);
    new_tx_id = tx_log_info->latest_tx_id;
    pthread_mutex_unlock(&tx_log_info->ltid_mutex);
    return new_tx_id;
}

int tx_log_get_ltid(tx_log_info_t *tx_log_info) {
    int ret;
    pthread_mutex_lock(&tx_log_info->ltid_mutex);
    ret = tx_log_info->latest_tx_id;
    pthread_mutex_unlock(&tx_log_info->ltid_mutex);
    return ret;
}