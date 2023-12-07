#include <stdio.h>
#include <string.h>
#include "input_handler.h"
#define DEFAULT_BUFFER_SIZE 127

char* get_input(char* buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        return NULL;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    return buffer;
}
int is_help_argument(const char* arg) {
    return strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0;
}

int is_buffer_argument(const char* arg) {
    return strcmp(arg, "-b") == 0 || strcmp(arg, "--buffer") == 0;
}

int parse_buffer_size(const char* arg) {
    return atoi(arg);
}
void print_help() {
    printf("Simplified Command Processor\n");
    printf("Options:\n");
    printf("-h or --help: Display this help message\n");
    printf("-b or --buffer <size>: Specify buffer size (default is %d)\n", DEFAULT_BUFFER_SIZE);
}






