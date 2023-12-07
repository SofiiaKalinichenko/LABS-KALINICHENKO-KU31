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
        printf("Process 1: Received signal from Process 2\n");

        int *sum = (int *)shmat(shmid, NULL, 0);
        printf("Process 1: Received sum: %d\n", *sum);
        shmdt(sum);

        printf("Process 1: Enter data (or -1 to exit): ");
        int data;
        scanf("%d", &data);

        int *data_ptr = (int *)shmat(shmid, NULL, 0);
        *data_ptr = data;
        shmdt(data_ptr);

        kill(getpid() + 1, SIGUSR1);

        if (data == -1) {
            printf("Process 1: Exiting...\n");
            exit(EXIT_SUCCESS);
        }
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

    while (*shm_ptr == 0) {
        sleep(1);
    }

    printf("Process 1: Initial signal received. Starting communication...\n");

    while (1) {
    }

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

