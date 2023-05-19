#pragma once

#include <pthread.h>

#include "../log/tx_log.h"

#define LOCAL_IPADDR        "127.0.0.1"
#define MASTER_PORT_OFFSET   5000
#define SLAVE_PORT_OFFSET   6000

#define FILENAME_SIZE       32
#define MIN_LSN             1

struct config_t {
    int finish_flag;                                    // システム終了フラグ（共有変数）
    pthread_mutex_t finish_flag_mutex;
    double exp_time;                                    // ベンチマーク計測時間
    double start_time;                                  // ベンチマーク開始時刻
    int sent_lsn[SLAVE_NODE_NUM];                       // 各スレーブに対する送信済みLSN（共有変数）
    pthread_mutex_t slsn_mutex[SLAVE_NODE_NUM];

    tx_log_info_t *tx_log_info;
};
typedef struct config_t config_t;

config_t *config_init(double exp_time, char *tx_log_filename);
void config_destroy(config_t *config);
int config_get_finish_flag(config_t *config);
void config_raise_finish_flag(config_t *config);
int config_get_sent_lsn(config_t *config, int slave_id);
void config_set_sent_lsn(config_t *config, int slave_id, int new_val);
int get_master_port();
int get_slave_port(int);