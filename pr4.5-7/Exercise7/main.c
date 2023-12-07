#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

// Constants for command line arguments
const char *HELP_OPTION = "-h";
const char *INFO_OPTION = "-i";
const char *SET_OPTION = "-s";
const char *ASSIGN_OPTION = "-a";
const char *DELETE_OPTION = "-d";
const char *CLEAR_OPTION = "-c";

// Function to print the environment variables
void print_environment() {
    char **env = environ;
    if (env == NULL || *env == NULL) {
        printf("Environment is empty.\n");
    } else {
        while (*env) {
            printf("%s\n", *env);
            env++;
        }
    }
}

// Function to print the help message
void print_help() {
    printf("Help:\n");
    printf("%s, --help\t\tShow this help message\n", HELP_OPTION);
    printf("%s, --info <variable>\tShow the value of an environment variable\n", INFO_OPTION);
    printf("%s, --set <variable=value>\tSet the value of an environment variable\n", SET_OPTION);
    printf("%s -v <variable> [value]\tSet a new value for an environment variable or delete it\n", ASSIGN_OPTION);
    printf("%s, --del <variable>\tDelete an environment variable\n", DELETE_OPTION);
    printf("%s, --clear\t\tClear the entire environment\n", CLEAR_OPTION);
}

// Function to print the value of an environment variable
void print_variable(const char *variable_name) {
    char *value = getenv(variable_name);
    if (value != NULL) {
        printf("%s=%s\n", variable_name, value);
    } else {
        printf("Variable %s is not present in the environment.\n", variable_name);
    }
}

// Function to set the value of an environment variable
void set_variable(const char *variable_name, const char *value) {
    setenv(variable_name, value, 1);
    printf("%s=%s\n", variable_name, value);
}

// Function to assign a new value to an environment variable or delete it
void assign_variable(const char *variable_name, const char *value) {
    if (value != NULL) {
        setenv(variable_name, value, 1);
        printf("%s=%s\n", variable_name, value);
    } else {
        unsetenv(variable_name);
        printf("Variable %s has been removed from the environment.\n", variable_name);
    }
}

// Function to delete an environment variable
void delete_variable(const char *variable_name) {
    unsetenv(variable_name);
    printf("Variable %s has been removed from the environment.\n", variable_name);
}

// Function to clear the entire environment
void clear_environment() {
    clearenv();
    printf("\nEnvironment has been cleared!\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || (strcmp(argv[1], HELP_OPTION) == 0) || (strcmp(argv[1], "--help") == 0)) {
        print_help();
    } else if ((strcmp(argv[1], INFO_OPTION) == 0) && argc == 3) {
        print_variable(argv[2]);
    } else if ((strcmp(argv[1], SET_OPTION) == 0) && argc == 4) {
        set_variable(argv[2], argv[3]);
    } else if ((strcmp(argv[1], ASSIGN_OPTION) == 0) && (argc == 4 || argc == 5) && (strcmp(argv[3], "-v") == 0)) {
        assign_variable(argv[2], (argc == 5) ? argv[4] : NULL);
    } else if ((strcmp(argv[1], DELETE_OPTION) == 0 || (strcmp(argv[1], "--del") == 0)) && argc == 3) {
        delete_variable(argv[2]);
    } else if ((strcmp(argv[1], CLEAR_OPTION) == 0) || (strcmp(argv[1], "--clear") == 0)) {
        clear_environment();
    } else {
        printf("Error: Unknown option. Use %s or %s for help.\n", HELP_OPTION, "--help");
        return 1;
    }

    return 0;
}
