#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>

#define SHM_SIZE 100

int shmid;

void sig_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("Process 2: Received signal from Process 1\n");

        int *data_ptr = (int *)shmat(shmid, NULL, 0);
        int data = *data_ptr;
        shmdt(data_ptr);

        int *sum = (int *)shmat(shmid, NULL, 0);
        *sum += data;
        shmdt(sum);

        kill(getpid() - 1, SIGUSR1);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <shm_identifier>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    key_t key = atoi(argv[1]);

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    int *shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    signal(SIGUSR1, sig_handler);

    printf("Process 2: Sending initial signal to Process 1...\n");
    *shm_ptr = 1;  

    while (1) {
    }

    shmdt(shm_ptr);

    return 0;
}

