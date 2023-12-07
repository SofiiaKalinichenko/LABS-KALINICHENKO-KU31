#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "signal_handlers.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_handlers>\n", argv[0]);
        return 1;
    }

    num_handlers = atoi(argv[1]);

    if (num_handlers < 1) {
        printf("Number of handlers should be greater than 0.\n");
        return 1;
    }

    register_signal_handlers();

    printf("Waiting for process termination handlers. PID = %d\n", getpid());

    while (1) {
    }

}
