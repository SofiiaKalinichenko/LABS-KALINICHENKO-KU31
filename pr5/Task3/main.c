#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DEFAULT_BUFFER_SIZE 127

void print_help();
void remove_newline(char *str);
int execute_command(const char *command);
void process_commands(const char *username, int buffer_size);

int main(int argc, char *argv[]);

void print_help() {
    printf("Спрощений Обробник Команд\n");
    printf("Параметри:\n");
    printf("-h або --help: Показати цей довідковий запис\n");
    printf("-b або --буфер <розмір>: Визначити розмір буфера (за замовчуванням %d)\n", DEFAULT_BUFFER_SIZE);
}

void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

int execute_command(const char *command) {
    int result = system(command);
    if (result != 0) {
        printf("Помилка виконання команди. Код повернення: %d\n", result);
    }
    return result;
}

void process_commands(const char *username, int buffer_size) {
    char *buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        perror("Помилка виділення пам'яті");
        exit(1);
    }

    while (1) {
        printf("[%s]$", username);
        if (fgets(buffer, buffer_size, stdin) == NULL) {
            break;
        }

        remove_newline(buffer);

        if (strcmp(buffer, "stop") == 0) {
            printf("Завершення програми\n");
            break;
        }

        printf("Ваша команда: %s\n", buffer);
        execute_command(buffer);
    }

    printf("Зачекайте 3 секунди...\n");
    sleep(3);
    system("clear");
    free(buffer);
}

int main(int argc, char *argv[]) {
    char username[51];
    int buffer_size = DEFAULT_BUFFER_SIZE;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if ((strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--буфер") == 0) && i + 1 < argc) {
            buffer_size = atoi(argv[i + 1]);
            if (buffer_size <= 0) {
                printf("Недійсний розмір буфера. Використовується розмір за замовчуванням: %d\n", DEFAULT_BUFFER_SIZE);
                buffer_size = DEFAULT_BUFFER_SIZE;
            }
        }
    }

    printf("Введіть ваше ім'я користувача: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        perror("Помилка зчитування імені користувача");
        return 1;
    }

    remove_newline(username);

    printf("Ви працюєте з обробником команд, %s\n", username);

    process_commands(username, buffer_size);

    return 0;
}
