#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

void executeParallelCommands(char *input);

int executeCommand(char *command) {
    int result = system(command);
    printf("Exit code: %d\n", result);
    return result;
}

void inputCommands(char *input) {
    printf("Enter commands (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        executeParallelCommands(input);
    }
}

void executeParallelCommands(char *input) {
    char *token = strtok(input, ";");

    while (token != NULL) {
        printf("Executing command: %s\n", token);
        int result = executeCommand(token);
        token = strtok(NULL, ";");
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    inputCommands(input);
    return 0;
}
