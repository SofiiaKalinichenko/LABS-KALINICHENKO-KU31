#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "signal_handlers.h"

int num_handlers;

void signal_handler(int signum) {
    static int count = 0;
    count++;
    printf("Handler %d: Delaying for 1 second. Signal %d received.\n", count, signum);
    sleep(1);
}

void register_signal_handlers() {
    for (int i = 1; i <= num_handlers; i++) {
        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            printf("Error registering handler for SIGINT.\n");
            exit(1);
        }
    }
}
