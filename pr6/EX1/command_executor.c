
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_commands(char* input) {
    char* token = strtok(input, ";");

    while (token != NULL) {
        printf("Executing command: %s\n", token);
        int result = system(token);
        printf("Exit code: %d\n", result);
        token = strtok(NULL, ";");
    }
}
