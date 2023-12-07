#include "header.h"

int main(int argc, char *argv[]) {
    int num_children = 1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            if (i + 1 < argc) {
                FILE_NAME = argv[i + 1];
                i++;
            } else {
                fprintf(stderr, "Error: Argument expected for option -f\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
            if (i + 1 < argc) {
                num_children = atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "Error: Argument expected for option -n\n");
                return 1;
            }
        }
    }

    for (int i = 1; i <= num_children; i++) {
        create_child_process(i);
    }

    for (int i = 1; i <= num_children; i++) {
        wait(NULL);
    }

    return 0;
}
