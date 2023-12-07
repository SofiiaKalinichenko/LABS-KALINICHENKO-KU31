#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_SIZE 100
#define SEM_COUNT 2

void error(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

int main() {
    key_t shm_key = ftok("server.c", 'R');
    key_t sem_key = ftok("server.c", 'S');

    int shm_id = shmget(shm_key, SHM_SIZE, IPC_CREAT | 0666);
    if (shm_id == -1)
        error("shmget");

    int sem_id = semget(sem_key, SEM_COUNT, IPC_CREAT | 0666);
    if (sem_id == -1)
        error("semget");

    struct sembuf sem_signal = {0, 1, 0};
    semop(sem_id, &sem_signal, 1);

    int input;
    printf("Client: Enter data: ");
    if (scanf("%d", &input) != 1) {
        fprintf(stderr, "Client: Invalid input. Please enter an integer.\n");
        exit(EXIT_FAILURE);
    }

    int *data = (int *)shmat(shm_id, NULL, 0);
    *data = input;

    struct sembuf sem_signal_data = {1, -1, 0};
    semop(sem_id, &sem_signal_data, 1);

    struct sembuf sem_wait = {1, 0, 0};
    semop(sem_id, &sem_wait, 1);

    printf("Client: Received processed data from server: %d\n", *data);

    shmdt(data);

    printf("Client: Exiting...\n");

    return 0;
}


