#include "header.h"

void create_child_process(int number) {
    pid_t pid = fork();

    if (pid == 0) {
        char filename[50];
        sprintf(filename, "%s_%d.txt", FILE_NAME, number);

        FILE *file = fopen(filename, "w");
        if (file != NULL) {
            for (int i = 0; i < number; i++) {
                double random_number = (double)rand() / RAND_MAX;
                fprintf(file, "%lf\n", random_number);
            }
            fclose(file);
        } else {
            fprintf(stderr, "Error: Unable to open file for writing at %s\n", filename);
            exit(1);
        }
        exit(0);
    }
}
