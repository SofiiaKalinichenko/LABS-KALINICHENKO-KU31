#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Генерація випадкової цифри від 0 до 9
int generateDigit() {
    return rand() % 10;
}

// Перевірка, чи є сімка в масиві цифр
int containsSeven(int digits[], int length) {
    for (int i = 0; i < length; ++i) {
        if (digits[i] == 7) {
            return 1; // Є сімка
        }
    }
    return 0; // Немає сімки
}

// Перевірка, чи всі цифри однакові в масиві
int allDigitsEqual(int digits[], int length) {
    for (int i = 1; i < length; ++i) {
        if (digits[i] != digits[0]) {
            return 0; // Не всі цифри однакові
        }
    }
    return 1; // Всі цифри однакові
}

// Основна функція гри
void playSlotMachine(int bet, int length) {
    int digits[length];

    // Генерація випадкових цифр
    for (int i = 0; i < length; ++i) {
        digits[i] = generateDigit();
        printf("%d ", digits[i]);
    }

    // Перевірка умов виграшу
    if (containsSeven(digits, length)) {
        printf("\nCongratulations! You got at least one 7. You win your bet: %d\n", bet);
    } else if (allDigitsEqual(digits, length)) {
        if (digits[0] == 7) {
            printf("\nCongratulations! You got all 7s. Your bet is tripled: %d\n", bet * 3);
        } else {
            printf("\nCongratulations! You got all identical digits. Your bet is doubled: %d\n", bet * 2);
        }
    } else {
        printf("\nSorry, you didn't win this time.\n");
    }
}

int main() {
    // Ініціалізація генератора випадкових чисел
    srand(time(NULL));

    int bet, length;

    // Отримання від гравця ставки та довжини послідовності цифр
    printf("Enter your bet: ");
    scanf("%d", &bet);

    printf("Enter the length of the sequence: ");
    scanf("%d", &length);

    // Перевірка на коректність введених даних
    if (bet <= 0 || length <= 0) {
        printf("Invalid input. Bet and length must be positive integers.\n");
        return 1;
    }

    // Запуск гри
    playSlotMachine(bet, length);

    return 0;
}

