#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int size;
    int capacity;
} ArrayList;

ArrayList* createArrayList(int capacity) {
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    if (list == NULL) {
        printf("Помилка при виділенні пам'яті для списку.\n");
        return NULL;
    }
    list->array = (int*)malloc(sizeof(int) * capacity);
    if (list->array == NULL) {
        printf("Помилка при виділенні пам'яті для масиву.\n");
        free(list);
        return NULL;
    }
    list->size = 0;
    list->capacity = capacity;
    return list;
}

void add(ArrayList* list, int item) {
    if (list->size >= list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
        if (list->array == NULL) {
            printf("Помилка при виділенні пам'яті для масиву.\n");
            return;
        }
    }
    list->array[list->size] = item;
    list->size++;
}

void insert(ArrayList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Недійсний індекс для вставки.\n");
        return;
    }
    if (list->size >= list->capacity) {
        // Збільшення ємності списку, якщо потрібно
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, sizeof(int) * list->capacity);
        if (list->array == NULL) {
            printf("Помилка при виділенні пам'яті для масиву.\n");
            return;
        }
    }
    for (int i = list->size; i > index; i--) {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = item;
    list->size++;
}

int size(ArrayList* list) {
    return list->size;
}

void removeAtIndex(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Недійсний індекс для видалення.\n");
        return;
    }
    for (int i = index; i < list->size - 1; i++) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

void set(ArrayList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("Недійсний індекс для зміни.\n");
        return;
    }
    list->array[index] = item;
}

void get(ArrayList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("Недійсний індекс для отримання.\n");
        return;
    }
    if(list->array[index] == 0 && list->size == 0 || index > list->size){
        printf("Недійсний індекс для отримання.\n");
        return;
    }
    printf("Значення за індексом %d: %d\n", index, list->array[index]);
}

void display(ArrayList* list) {
    printf("Елементи списку: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->array[i]);
    }
    printf("\n");
}

void destroyArrayList(ArrayList* list) {
    free(list->array);
    free(list);
}

int main() {
    int capacity;
    printf("Введіть початкову ємність списку: ");
    scanf("%d", &capacity);

    ArrayList* list = createArrayList(capacity);
    if (list == NULL) {
        return 1;
    }

    int choice, item, index;

    do {
        printf("\nМеню операцій:\n");
        printf("1. Додати елемент в кінець списку\n");
        printf("2. Вставити елемент за вказаним індексом\n");
        printf("3. Видалити елемент за вказаним індексом\n");
        printf("4. Змінити значення елемента за вказаним індексом\n");
        printf("5. Отримати значення елемента за вказаним індексом\n");
        printf("6. Показати розмір списку\n");
        printf("7. Показати всі елементи списку\n");
        printf("8. Вийти\n");

        printf("Виберіть операцію: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введіть елемент для додавання: ");
                scanf("%d", &item);
                add(list, item);
                break;
            case 2:
                if (list->size == 0) {
                    printf("Список порожній.\n");
                    break;
                }
                printf("Введіть індекс для вставки: ");
                scanf("%d", &index);
                printf("Введіть елемент для вставки: ");
                scanf("%d", &item);
                insert(list, index, item);
                break;
            case 3:
                if (list->size == 0) {
                    printf("Список порожній.\n");
                    break;
                }
                printf("Введіть індекс для видалення: ");
                scanf("%d", &index);
                removeAtIndex(list, index);
                break;
            case 4:
                if (list->size == 0) {
                    printf("Список порожній.\n");
                    break;
                }
                printf("Введіть індекс для зміни: ");
                scanf("%d", &index);
                printf("Введіть нове значення: ");
                scanf("%d", &item);
                set(list, index, item);
                break;
            case 5:
                if (list->size == 0) {
                    printf("Список порожній.\n");
                    break;
                }
                printf("Введіть індекс для отримання: ");
                scanf("%d", &index);
                get(list,index);
                break;
            case 6:
                if (list->size == 0) {
                    printf("Список порожній.\n");
                    break;
                }
                printf("Розмір списку: %d\n", size(list));
                break;
            case 7:
                if (list->size == 0) {
                    printf("Список порожній.\n");
                    break;
                }
                display(list);
                break;
            case 8:
                break;
            default:
                printf("Невірний вибір операції. Спробуйте ще раз.\n");
                break;
        }
    } while (choice != 8);
    destroyArrayList(list);
    return 0;
}
