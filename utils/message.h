#pragma once

enum message_enum {
    LOG,
    LOG_ACK,
    FINISH_NOTIFICATION,
};
typedef enum message_enum message_enum;

struct message_t {
    char *data;
    message_enum type;
};
typedef struct message_t message_t;