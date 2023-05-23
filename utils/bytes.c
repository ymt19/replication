#include <stdio.h>
#include <string.h>

#include "../utils/bytes.h"

void set_int_to_bytes(char *bytes, int offset, int value) {
    memcpy(bytes + offset, &value, sizeof(int));
}

int get_int_from_bytes(char *bytes, int offset) {
    int value;
    memcpy(&value, bytes + offset, sizeof(int));
    return value;
}

void set_short_int_to_bytes(char *bytes, int offset, short value) {
    memcpy(bytes + offset, &value, sizeof(short));
}

short get_short_int_from_bytes(char *bytes, int offset) {
    short value;
    memcpy(&value, bytes + offset, sizeof(short));
    return value;
}

void set_char_to_bytes(char *bytes, int offset, char value) {
    memcpy(bytes + offset, &value, sizeof(char));
}

char get_char_from_bytes(char *bytes, int offset) {
    char value;
    memcpy(&value, bytes + offset, sizeof(char));
    return value;
}

void set_str_to_bytes(char *bytes, int offset, int len, char *str) {
    memcpy(bytes + offset, str, sizeof(char) * len);
}

void get_str_from_bytes(char *bytes, int offset, int len, char *str) {
    memcpy(str, bytes + offset, sizeof(char) * len);
}