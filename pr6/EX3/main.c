#include <stdio.h>
#include <stdlib.h>
#include "input_handler.h"
#include "command_executor.h"

#define DEFAULT_BUFFER_SIZE 127

int main(int argc, char *argv[]) {
    char username[50];
    int buffer_size = DEFAULT_BUFFER_SIZE;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));

    if (buffer == NULL) {
        perror("Memory allocation error");
        return 1;
    }

    printf("Enter your username: ");
    if (get_input(username, sizeof(username)) == NULL) {
        perror("Error reading username");
        free(buffer);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (is_help_argument(argv[i])) {
            print_help();
            free(buffer);
            return 0;
        } else if (is_buffer_argument(argv[i]) && i + 1 < argc) {
            buffer_size = parse_buffer_size(argv[i + 1]);
            if (buffer_size <= 0) {
                printf("Invalid buffer size. Using the default size: %d\n", DEFAULT_BUFFER_SIZE);
                buffer_size = DEFAULT_BUFFER_SIZE;
            }
            i++;
        }
    }

    printf("You are working with the command processor, %s\n", username);

    while (1) {
        printf("[%s]$", username);
        if (get_input(buffer, buffer_size) == NULL) {
            break;
        }

        if (is_stop_command(buffer)) {
            printf("Program termination\n");
            break;
        }

        printf("Your command: %s\n", buffer);
        int result = execute_command(buffer);

        if (result != 0) {
            printf("Error executing the command. Return code: %d\n", result);
        }
    }

    printf("Wait 3 seconds...\n");
    sleep(3);
    system("clear");
    free(buffer);
    return 0;
}
