#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void custom_alarm(const char *message) {
    printf("ALARM: %s\n", message);
}

void custom_pause(int seconds) {
    sleep(seconds);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interval_seconds> <message>\n", argv[0]);
        return 1;
    }

    int interval = atoi(argv[1]);
    const char *message = argv[2];

    printf("Setting alarm for %d seconds with message: %s\n", interval, message);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Failed to fork");
        return 1;
    } else if (child_pid == 0) {
        custom_pause(interval);
        custom_alarm(message);
        exit(0);
    } else {
        return 0;
    }
}

