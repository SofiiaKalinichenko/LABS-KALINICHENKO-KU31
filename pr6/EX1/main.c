#include <stdio.h>
#include <string.h>
#include "input_handler.h"
#include "command_executor.h"

int main() {
    char input[1024];

    printf("Enter commands (type 'exit' to quit):\n");

    while (1) {
        printf("> ");
        if (get_input(input, sizeof(input)) == NULL) {
            break;
        }

        if (strcmp(input, "exit") == 0) {
            break;
        }

        execute_commands(input);
    }

    return 0;
}
