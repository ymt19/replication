#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "../master/semisync_sender.h"
#include "../network/tcp/tcp_client.h"
#include "../network/tcp/tcp_server.h"
#include "../network/udp/udp_client.h"
#include "../network/udp/udp_server.h"
#include "../utils/config.h"

struct sender_thread_info_t {
    config_t *config;
    int connection_slave_id;
};
typedef struct sender_thread_info_t sender_thread_info_t;

void *semisync_tcp_sender(sender_thread_info_t *arg);
void *semisync_udp_sender(sender_thread_info_t *arg);

void *semisync_sender(config_t *config) {
    int ret;
    pthread_t sender_thread[SLAVE_NODE_NUM];
    sender_thread_info_t *sender_thread_info;

    sender_thread_info = malloc(sizeof(sender_thread_info_t) * SLAVE_NODE_NUM);

    // レプリカに対するsender threadを開始
    for (int slave_id = 0; slave_id < SLAVE_NODE_NUM; slave_id++) {
        sender_thread_info[slave_id].config =config;
        sender_thread_info[slave_id].connection_slave_id = slave_id;
        #if TCP
        // ret = pthread_create(&sender_thread[slave_id], 
        //                     NULL,
        //                     (void *)semisync_tcp_sender,
        //                     (void *)&sender_thread_info[slave_id]);
        // if (ret != 0) {
        //     exit(1);
        // }
        #elif NONCOOP   // 従来
        ret = pthread_create(&sender_thread[slave_id], 
                            NULL,
                            (void *)semisync_udp_sender,
                            (void *)&sender_thread_info[slave_id]);
        if (ret != 0) {
            exit(1);
        }
        #elif COOP      // 提案
        // ret = pthread_create(&sender_thread[slave_id], 
        //                     NULL,
        //                     (void *)semisync_udp_sender,
        //                     (void *)&sender_thread_info[slave_id]);
        // if (ret != 0) {
        //     exit(1);
        // }
        #endif
    }

    for (int slave_id = 0; slave_id < SLAVE_NODE_NUM; slave_id++) {
        ret = pthread_join(sender_thread[slave_id], NULL);
        if (ret != 0) {
            exit(1);
        }
    }
    
    free(sender_thread_info);
}

void *semisync_tcp_sender(sender_thread_info_t *arg) {
    printf("tcp replica%d\n", arg->connection_slave_id);
}

void *semisync_udp_sender(sender_thread_info_t *arg) {
    config_t *config = arg->config;
    tx_log_info_t *tx_log_info = config->tx_log_info;
    int my_port;
    int connection_slave_port;
    // char connection_slave_ipaddr[32];
    udp_cl_info_t udp_cl_info;
    udp_sv_info_t udp_sv_info;
    int send_msg_len;
    int success_send_msg_len;
    char send_msg[BUFSIZ];
    int recv_msg_len;
    char recv_msg[BUFSIZ];
    char errmsg[256];

    my_port = get_master_port(arg->connection_slave_id);
    connection_slave_port = get_slave_port(arg->connection_slave_id);
    udp_cl_socket_init(&udp_cl_info, 0, errmsg);
    udp_sv_socket_init(&udp_sv_info, my_port, 0, errmsg);

    int latest_lsn, sent_lsn;
    while(!config_get_finish_flag(config)) {
        latest_lsn = tx_log_get_ltid(tx_log_info);
        sent_lsn = config_get_sent_lsn(config, arg->connection_slave_id);
        if (latest_lsn > sent_lsn) {
            // lsn[sent_lsn+1]をslaveに送信

            sprintf(send_msg, "[msg]master->replica%d lsn%d", arg->connection_slave_id, sent_lsn+1);
            send_msg_len = strlen(send_msg);
            printf("[send] %s\n", send_msg);
            udp_cl_send_msg(&udp_cl_info,
                            send_msg,
                            send_msg_len,
                            LOCAL_IPADDR,
                            connection_slave_port,
                            errmsg);
            
            recv_msg_len = udp_sv_recieve_msg(&udp_sv_info,
                                            recv_msg,
                                            BUFSIZ,
                                            errmsg);
            printf("%s\n", recv_msg);

            // ACK受信後、sent_lsnをインクリメント
            config_set_sent_lsn(config, arg->connection_slave_id, sent_lsn+1);
        }
    }
    printf("semisync sender finish%d\n", arg->connection_slave_id);

    udp_cl_socket_deinit(&udp_cl_info);
    udp_sv_socket_deinit(&udp_sv_info);
}