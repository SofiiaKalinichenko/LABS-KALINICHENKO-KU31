#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int num_handlers;

void signal_handler(int signum);
void print_usage(const char *program_name);
void wait_for_termination_handlers();
void register_signal_handlers();

void signal_handler(int signum) {
    static int count = 0;
    count++;
    printf("Обробник %d: Затримка на 1 секунду. Сигнал %d отримано.\n", count, signum);
    sleep(1);
}

void print_usage(const char *program_name) {
    printf("Використання: %s <кількість_обробників>\n", program_name);
}

void wait_for_termination_handlers() {
    while (1) {
    }
}

void register_signal_handlers() {
    for (int i = 1; i <= num_handlers; i++) {
        if (signal(SIGINT, signal_handler) == SIG_ERR) {
            perror("Помилка реєстрації обробника для SIGINT");
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }

    num_handlers = atoi(argv[1]);

    if (num_handlers < 1) {
        printf("Кількість обробників повинна бути більше 0.\n");
        return 1;
    }

    printf("Очікування обробників завершення процесу. PID = %d\n", getpid());

    register_signal_handlers();
    wait_for_termination_handlers();

    return 0;
}
