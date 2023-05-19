#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "../log/tx_log.h"
#include "../master/async_sender.h"
#include "../master/semisync_sender.h"
#include "../utils/config.h"
#include "../utils/timer.h"

#define ASYNC               1
#define SEMISYNC            2

#define CLIENT_THREAD_NUM   5

struct client_thread_info_t {
    unsigned short client_id;
    config_t *config;
    tx_log_info_t *tx_log_info;
};
typedef struct client_thread_info_t client_thread_info_t;

void *client(client_thread_info_t *info);

int main(int argc, char *argv[]) {
    int ret;
    config_t *config;
    double exp_time;
    pthread_t sender_main_thread;
    pthread_t client_thread[CLIENT_THREAD_NUM];
    client_thread_info_t *client_thread_info_set;

    if (argc != 2) {
        printf("<experiment time>[sec]\n");
        exit(1);
    }
    exp_time = atoi(argv[1]);

    config = config_init(exp_time, "master_tx_log.csv");


    // sender起動
    #if REPLICATION == ASYNC
    printf("Asynchronous replication...\n");
    ret = pthread_create(&sender_main_thread, 
                        NULL,
                        (void *)async_sender,
                        (void *)config);
    if (ret != 0) {
        exit(1);
    }
    #elif REPLICATION == SEMISYNC
    printf("SEMIsynchronous replication...\n");
    ret = pthread_create(&sender_main_thread, 
                        NULL,
                        (void *)semisync_sender,
                        (void *)config);
    if (ret != 0) {
        exit(1);
    }
    #endif


    // client起動（ログ書き込みmaster_log.csv
    client_thread_info_set = malloc(sizeof(client_thread_info_t) * CLIENT_THREAD_NUM);
    config->start_time = get_time();

    #if REPLICATION == ASYNC

    #elif REPLICATION == SEMISYNC
    for (int client_id = 0; client_id < CLIENT_THREAD_NUM; client_id++) {
        client_thread_info_set[client_id].config = config;
        client_thread_info_set[client_id].client_id = client_id;
        ret = pthread_create(&client_thread[client_id], 
                            NULL,
                            (void *)client,
                            (void *)&client_thread_info_set[client_id]);
        if (ret != 0) {
            exit(1);
        }
    }
    #endif
    for (int client_id = 0; client_id < CLIENT_THREAD_NUM; client_id++) {
        ret = pthread_join(client_thread[client_id], NULL);
        if (ret != 0) {
            exit(1);
        }
    }

    // client終了後，終了フラグを立てる
    config_raise_finish_flag(config);

    ret = pthread_join(sender_main_thread, NULL);
    if (ret != 0) {
        exit(1);
    }

    config_destroy(config);

    return 0;
}

void *client(client_thread_info_t *info) {
    config_t *config = info->config;
    tx_log_info_t *tx_log_info = info->config->tx_log_info;
    int client_id = info->client_id;
    int tx_id;
    double call_time;
    double response_time;

    printf("client%d\n", client_id);
    while (config->start_time + config->exp_time > get_time()) {
        call_time = get_time() - config->start_time;
        tx_id = tx_log_append(tx_log_info);

        #if REPLICATION == SEMISYNC
        for (int client_id = 0; client_id < SLAVE_NODE_NUM; client_id++) {
            while(!(config_get_sent_lsn(config, client_id) >= tx_id)) {}
        }
        #endif
        response_time = get_time() - config->start_time;
        
        printf("[response] clientid:%d, txid:%d, call:%lf, response:%lf\n", client_id, tx_id, call_time, response_time);
        sleep(1);
    }
}