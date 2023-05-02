#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../log/tx_log.h"

tx_log_info_t *tx_log_info_init(char *filename) {
    tx_log_info_t *tx_log_info;

    tx_log_info = malloc(sizeof(tx_log_info_t));
    
    strcpy(tx_log_info->filename, filename);
    pthread_mutex_init(&tx_log_info->ltid_mutex, NULL);
    tx_log_info->latest_tx_id = -1;

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
void tx_log_append(tx_log_info_t *tx_log_info) {
    pthread_mutex_lock(&tx_log_info->ltid_mutex);
    printf("start\n");
    printf("%d\n", ++tx_log_info->latest_tx_id);
    printf("end\n");
    pthread_mutex_unlock(&tx_log_info->ltid_mutex);
}

void tx_log_write(tx_log_info_t *tx_log_info, tx_t tx) {

}

void tx_log_read(tx_log_info_t *tx_log_info, tx_t *tx, int tx_id) {
    printf("2\n");
}