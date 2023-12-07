#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (environ == NULL) {
        printf("Environment is not available.\n");
        return 1;
    }
    if (argc < 2) {
        if (clearenv() == 0) {
            printf("All environment variables have been cleared.\n");
        } else {
            perror("Error clearing the environment");
        }
    } else {
        const char *var_name = argv[1];
        if (unsetenv(var_name) == 0) {
            printf("Environment variable %s has been removed.\n", var_name);
        } else {
            perror("Error removing environment variable");
        }
    }
    char **env = environ;
    while (*env) {
        printf("%s\n", *env);
        env++;
    }
    return 0;
}
