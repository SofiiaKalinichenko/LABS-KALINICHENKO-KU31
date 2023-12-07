#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Enter: <variable> <value>\n Usage: %s ", argv[0]);
        return 1;
    }
    const char *environment_variable = argv[1];
    const char *value = argv[2];
    if (setenv(environment_variable, value, 1) != 0) {
        perror("Error setting environment variable");
        return 1;
    }
    char *env_value = getenv(environment_variable);
    if (env_value != NULL) {
        printf("Environment Variable: %s\nValue: %s\n", environment_variable, env_value);
    } else {
        printf("The environment variable was not set or an error occurred.\n");
    }
    return 0;
}
