#include <stdlib.h>
#include <unistd.h>
#include "command_executor.h"

int execute_command(char* command) {
    int result = system(command);
    return result;
}

int is_stop_command(const char* command) {
    return strcmp(command, "stop") == 0;
}
