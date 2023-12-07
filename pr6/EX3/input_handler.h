#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

char* get_input(char* buffer, size_t size);
int is_help_argument(const char* arg);
int is_buffer_argument(const char* arg);
int parse_buffer_size(const char* arg);
void print_help();

#endif
