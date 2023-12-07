#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Enter: <variable_name>\n Usage: %s ", argv[0]);
        return 1;
    }
    char *env_variable_name = argv[1];
    char *env_variable_value = getenv(env_variable_name);
    if (env_variable_value != NULL) {printf("Environment variable %s has the value: %s\n", env_variable_name, env_variable_value);} else {printf("Environment variable %s not found\n", env_variable_name);}
    return 0;
}
