#include "../utils/message.h"
#include "../utils/bytes.h"

message_enum identify_message_types(char *msg) {
    char type = get_char_from_bytes(msg, COMMON_HEADER_OFFSET_TYPE);
    if (type == E_LOG) {
        return E_LOG;
    } else if (type == E_LOG_ACK) {
        return E_LOG_ACK;
    } else if (type == E_FINISH_NOTIFICATION) {
        return E_FINISH_NOTIFICATION;
    } else if (type == E_FINISH_NOTIFICATION_ACK) {
        return E_FINISH_NOTIFICATION_ACK;
    } else {
        E_ERROR;
    }
}

int create_log_msg(char *msg, int seq_num, char *log, int log_size) {
    set_char_to_bytes(msg, COMMON_HEADER_OFFSET_TYPE, E_LOG);
    set_int_to_bytes(msg, LOG_HEADER_OFFSET_SEQ_NUM, seq_num);
    set_int_to_bytes(msg, LOG_HEADER_OFFSET_DATA_SIZE, log_size);
    set_str_to_bytes(msg, LOG_DATA_OFFSET, log_size, log);
    return LOG_HEADER_SIZE + log_size;
}

/**
 * @brief Get the msg log object
 * 
 * @param msg 
 * @param log 
 * @return int seaqence number
 */
int get_info_from_log_msg(char *msg, char *log) {
    int seq_num, log_size;
    seq_num = get_int_from_bytes(msg, LOG_HEADER_OFFSET_SEQ_NUM);
    log_size = get_int_from_bytes(msg, LOG_HEADER_OFFSET_DATA_SIZE);
    get_str_from_bytes(msg, LOG_DATA_OFFSET, log_size, log);
    return seq_num;
}

int create_log_ack_msg(char *msg, int seq_num) {
    set_char_to_bytes(msg, COMMON_HEADER_OFFSET_TYPE, E_LOG_ACK);
    set_int_to_bytes(msg, LOG_ACK_HEADER_OFFSET_SEQ_NUM, seq_num);
    return LOG_ACK_HEADER_SIZE;
}

int get_info_from_log_ack_msg(char *msg) {
    int seq_num;
    seq_num = get_int_from_bytes(msg, LOG_ACK_HEADER_OFFSET_SEQ_NUM);
    return seq_num;
}

int create_log_req_msg(char *msg, int seq_num) {
    set_char_to_bytes(msg, COMMON_HEADER_OFFSET_TYPE, E_LOG_REQ);
    set_int_to_bytes(msg, LOG_REQ_HEADER_OFFSET_SEQ_NUM, seq_num);
    return LOG_REQ_HEADER_SIZE;
}

int get_info_from_log_req_msg(char *msg) {
    int seq_num;
    seq_num = get_int_from_bytes(msg, LOG_REQ_HEADER_OFFSET_SEQ_NUM);
    return seq_num;
}

int create_fin_not_msg(char *msg) {
    set_char_to_bytes(msg, COMMON_HEADER_OFFSET_TYPE, E_FINISH_NOTIFICATION);
    return FIN_NOT_HEADER_SIZE;
}

int create_fin_not_ack_msg(char *msg) {
    set_char_to_bytes(msg, COMMON_HEADER_OFFSET_TYPE, E_FINISH_NOTIFICATION_ACK);
    return FIN_NOT_ACK_HEADER_SIZE;
}