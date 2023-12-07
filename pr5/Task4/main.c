#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_FILENAME_LENGTH 50

void create_child_process(const char *file_name, int number);
void process_command_line_args(int argc, char *argv[], const char **file_name, int *num_children);
void write_data_to_file(const char *file_name, int number);

int main(int argc, char *argv[]) {
    const char *file_name = "default";
    int num_children = 1;

    process_command_line_args(argc, argv, &file_name, &num_children);

    for (int i = 1; i <= num_children; i++) {
        create_child_process(file_name, i);
    }

    for (int i = 1; i <= num_children; i++) {
        wait(NULL);
    }

    return 0;
}

void create_child_process(const char *file_name, int number) {
    pid_t pid = fork();

    if (pid == 0) {
        write_data_to_file(file_name, number);
        exit(0);
    }
}

void write_data_to_file(const char *file_name, int number) {
    char filename[MAX_FILENAME_LENGTH];
    snprintf(filename, sizeof(filename), "%s_%d.txt", file_name, number);

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < number; i++) {
            double random_number = (double)rand() / RAND_MAX;
            fprintf(file, "%lf\n", random_number);
        }
        fclose(file);
    } else {
        fprintf(stderr, "Помилка: Неможливо відкрити файл для запису за шляхом %s\n", filename);
        exit(1);
    }
}

void process_command_line_args(int argc, char *argv[], const char **file_name, int *num_children) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                *file_name = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "Помилка: Для параметру -f очікується аргумент\n");
                exit(1);
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                *num_children = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Помилка: Для параметру -n очікується аргумент\n");
                exit(1);
            }
        }
    }
}
