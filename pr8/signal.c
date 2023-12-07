#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handle_signal(int signo) {
    switch (signo) {
        case SIGINT:
            printf("Caught SIGINT signal\n");
            break;
        case SIGTERM:
            printf("Caught SIGTERM signal\n");
            break;
        case SIGUSR1:
            printf("Caught SIGUSR1 signal. Exiting...\n");
            exit(0);
            break;
        case SIGPROF:
            signal(SIGPROF, SIG_DFL);
            break;
        case SIGHUP:
            break;
        default:
            break;
    }
}

int main() {
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGUSR1, handle_signal);
    signal(SIGPROF, handle_signal);
    signal(SIGHUP, SIG_IGN);

    printf("Process ID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1) {
        pause();
    }

    return 0;
}

