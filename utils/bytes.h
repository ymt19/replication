#pragma once

void set_int_to_bytes(char *bytes, int offset, int value);
int get_int_from_bytes(char *bytes, int offset);
void set_short_int_to_bytes(char *bytes, int offset, short value);
short get_short_int_from_bytes(char *bytes, int offset);
void set_char_to_bytes(char *bytes, int offset, char value);
char get_char_from_bytes(char *bytes, int offset);
void set_str_to_bytes(char *bytes, int offset, int len, char *str);
void get_str_from_bytes(char *bytes, int offset, int len, char *str);