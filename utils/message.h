#pragma once

enum message_enum {
    E_LOG,
    E_LOG_ACK,
    E_LOG_REQ,
    E_FINISH_NOTIFICATION,
    E_FINISH_NOTIFICATION_ACK,
    E_ERROR,
};
typedef enum message_enum message_enum;

message_enum identify_message_types(char *msg);
int create_log_msg(char *msg, int seq_num, char *log, int log_size);
int get_info_from_log_msg(char *msg, char *log);
int create_log_ack_msg(char *msg, int seq_num);
int get_info_from_log_ack_msg(char *msg);
int create_log_req_msg(char *msg, int seq_num);
int get_info_from_log_req_msg(char *msg);
int create_fin_not_msg(char *msg);
int create_fin_not_ack_msg(char *msg);

// メッセージ共通ヘッダオフセット
#define COMMON_HEADER_OFFSET_TYPE   0

// LOGメッセージヘッダオフセット
#define LOG_HEADER_OFFSET_SEQ_NUM       COMMON_HEADER_OFFSET_TYPE + sizeof(char)
#define LOG_HEADER_OFFSET_DATA_SIZE     LOG_HEADER_OFFSET_SEQ_NUM + sizeof(int)
// LOGメッセージヘッダサイズ
#define LOG_HEADER_SIZE                 LOG_HEADER_OFFSET_DATA_SIZE + sizeof(int)
// LOGメッセージデータオフセット
#define LOG_DATA_OFFSET                 LOG_HEADER_SIZE

// LOG_ACKメッセージヘッダオフセット
#define LOG_ACK_HEADER_OFFSET_SEQ_NUM   COMMON_HEADER_OFFSET_TYPE + sizeof(char)
// LOG_ACKメッセージヘッダサイズ
#define LOG_ACK_HEADER_SIZE             LOG_ACK_HEADER_OFFSET_SEQ_NUM + sizeof(int)

// LOG_REQメッセージヘッダオフセット
#define LOG_REQ_HEADER_OFFSET_SEQ_NUM   COMMON_HEADER_OFFSET_TYPE + sizeof(char)
// LOG_REQメッセージヘッダサイズ
#define LOG_REQ_HEADER_SIZE             LOG_REQ_HEADER_OFFSET_SEQ_NUM + sizeof(int)

// FIN_NOTメッセージヘッダサイズ
#define FIN_NOT_HEADER_SIZE             COMMON_HEADER_OFFSET_TYPE + sizeof(char)

// FIN_NOT_ACKメッセージヘッダサイズ
#define FIN_NOT_ACK_HEADER_SIZE         COMMON_HEADER_OFFSET_TYPE + sizeof(char)