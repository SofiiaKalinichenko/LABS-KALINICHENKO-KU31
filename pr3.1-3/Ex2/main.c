#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
    int size;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct LinkedList* createLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void add(struct LinkedList* list, int item) {
    struct Node* newNode = createNode(item);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void insert(struct LinkedList* list, int index, int item) {
    if (index < 0 || index > list->size) {
        printf("Помилка: Неправильний індекс для вставки\n");
        return;
    }
    struct Node* newNode = createNode(item);
    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
    printf("\nЕлемент вставлено.\n");
}

int size(struct LinkedList* list) {
    return list->size;
}

void removeElement(struct LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("\nПомилка: Неправильний індекс для видалення\n");
        return;
    }
    if (index == 0) {
        struct Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        struct Node* temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    list->size--;
    printf("\nЕлемент видалено.\n");
}

void set(struct LinkedList* list, int index, int item) {
    if (index < 0 || index >= list->size) {
        printf("\nПомилка: Неправильний індекс для заміни\n");
        return;
    }
    struct Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = item;
    printf("\nЕлемент замінено.\n");
}

int get(struct LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("\nПомилка: Неправильний індекс для отримання\n");
        return -1;
    }
    struct Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void printList(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void displayMenu() {
    printf("\nВиберіть опцію:\n");
    printf("1. Додати елемент в кінець списку\n");
    printf("2. Вставити елемент за індексом\n");
    printf("3. Отримати кількість елементів у списку\n");
    printf("4. Видалити елемент за індексом\n");
    printf("5. Замінити елемент за індексом\n");
    printf("6. Отримати значення за індексом\n");
    printf("7. Вивести список\n");
    printf("0. Вихід\n");
    printf("Ваш вибір: ");
}

int main() {
    struct LinkedList* list = createLinkedList();

    int choice;
    int item, index;

    while (1) {
        displayMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введіть значення елемента: ");
                scanf("%d", &item);
                add(list, item);
                printf("Елемент додано в кінець списку.\n");
                break;
            case 2:
                if(list->size == 0){
                    printf("\nСписок пустий!\n");
                    break;
                }
                printf("Введіть індекс для вставки: ");
                scanf("%d", &index);
                printf("Введіть значення елемента: ");
                scanf("%d", &item);
                insert(list, index, item);
                break;
            case 3:
                if(list->size == 0){
                    printf("\nСписок пустий!\n");
                    break;
                }
                printf("Кількість елементів у списку: %d\n", size(list));
                break;
            case 4:
                if(list->size == 0){
                    printf("\nСписок пустий!\n");
                    break;
                }
                printf("Введіть індекс для видалення: ");
                scanf("%d", &index);
                removeElement(list, index);
                break;
            case 5:
                if(list->size == 0){
                    printf("\nСписок пустий!\n");
                    break;
                }
                printf("Введіть індекс для заміни: ");
                scanf("%d", &index);
                printf("Введіть нове значення елемента: ");
                scanf("%d", &item);
                set(list, index, item);
                break;
            case 6:
                if(list->size == 0){
                    printf("\nСписок пустий!\n");
                    break;
                }
                printf("Введіть індекс для отримання: ");
                scanf("%d", &index);
                item = get(list, index);
                if (item != -1) {
                    printf("\nЗначення елемента: %d\n", item);
                }
                break;
            case 7:
                if(list->size == 0){
                    printf("\nСписок пустий!\n");
                    break;
                }
                printf("\nСписок: ");
                printList(list);
                break;
            case 0:
                free(list);
                return 0;
            default:
                printf("\nНеправильний вибір. Спробуйте ще раз.\n");
        }
    }
    return 0;
}
