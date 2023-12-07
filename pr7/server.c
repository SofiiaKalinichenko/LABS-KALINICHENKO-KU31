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

    semctl(sem_id, 0, SETVAL, 0); 
    semctl(sem_id, 1, SETVAL, 1); 

    printf("Server: Waiting for data...\n");

    struct sembuf sem_wait = {0, -1, 0};
    semop(sem_id, &sem_wait, 1);

    int *data = (int *)shmat(shm_id, NULL, 0);
    if (data == (int *)-1)
        error("shmat");

    struct sembuf sem_wait_data = {1, -1, 0};
    semop(sem_id, &sem_wait_data, 1);

    printf("Server: Received data from client: %d\n", *data);

    *data *= 2;

    struct sembuf sem_signal = {1, 1, 0};
    semop(sem_id, &sem_signal, 1);

    shmdt(data);
    shmctl(shm_id, IPC_RMID, NULL);

    semctl(sem_id, 0, IPC_RMID, 0);
    semctl(sem_id, 1, IPC_RMID, 0);

    printf("Server: Exiting...\n");

    return 0;
}

