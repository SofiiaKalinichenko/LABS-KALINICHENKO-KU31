#include <stdio.h>
#include <stdlib.h>

int main() {
    char** env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
