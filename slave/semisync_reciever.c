#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../slave/semisync_reciever.h"
#include "../network/tcp/tcp_client.h"
#include "../network/tcp/tcp_server.h"
#include "../network/udp/udp_client.h"
#include "../network/udp/udp_server.h"
#include "../utils/config.h"

void semisync_tcp_reciever(int slave_id);
void semisync_udp_noncoop_reciever(int slave_id);
void semisync_udp_coop_reciever(int slave_id);

void semisync_reciever(int slave_id) {
    #if TCP
    semisync_tcp_reciever(slave_id);
    #elif NONCOOP
    printf("udp noncoop reciever\n");
    semisync_udp_noncoop_reciever(slave_id);
    #elif COOP
    semisync_udp_coop_reciever(slave_id);
    #endif
}

void semisync_tcp_reciever(int slave_id) {

}

void semisync_udp_noncoop_reciever(int slave_id) {
    int my_port;
    int master_port;
    // char master_ipaddr[32];
    udp_cl_info_t udp_cl_info;
    udp_sv_info_t udp_sv_info;
    int send_msg_len;
    int success_send_msg_len;
    char send_msg[BUFSIZ];
    int recv_msg_len;
    char recv_msg[BUFSIZ];
    char errmsg[256];

    my_port = get_slave_port(slave_id);
    master_port = get_master_port(slave_id);
    udp_cl_socket_init(&udp_cl_info, 0, errmsg);
    udp_sv_socket_init(&udp_sv_info, my_port, 0, errmsg);

    int cnt = 0;
    while(1) {
        cnt++;
        recv_msg_len = udp_sv_recieve_msg(&udp_sv_info,
                                          recv_msg,
                                          BUFSIZ,
                                          errmsg);
        printf("%s\n", recv_msg);

        sprintf(send_msg, "[ack]slave%d->master count%d", slave_id, cnt);
        send_msg_len = strlen(send_msg);
        udp_cl_send_msg(&udp_cl_info,
                        send_msg,
                        send_msg_len,
                        LOCAL_IPADDR,
                        master_port,
                        errmsg);
    }

    udp_cl_socket_deinit(&udp_cl_info);
    udp_sv_socket_deinit(&udp_sv_info);
}

void semisync_udp_coop_reciever(int slave_id) {

}