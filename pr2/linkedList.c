#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

struct LinkedList* initializeLinkedList() {
    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    list->head = NULL;
    return list;
}

void add(struct LinkedList* list, int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void insert(struct LinkedList* list, int index, int item) {
    if (index < 0) {
        printf("Index must be non-negative.\n");
        return;
    }

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1 && current != NULL; i++) {
            current = current->next;
        }

        if (current == NULL) {
            printf("Index out of bounds.\n");
            return;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}

// Отримання розміру списку
int size(struct LinkedList* list) {
    int count = 0;
    struct Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void removeAt(struct LinkedList* list, int index) {
    if (index < 0 || index >= size(list)) {
        printf("Index out of bounds.\n");
        return;
    }

    struct Node* temp;
    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        struct Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = current->next->next;
    }

    free(temp);
}

void set(struct LinkedList* list, int index, int item) {
    if (index < 0 || index >= size(list)) {
        printf("Index out of bounds.\n");
        return;
    }

    struct Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    current->data = item;
}

int get(struct LinkedList* list, int index) {
    if (index < 0 || index >= size(list)) {
        printf("Index out of bounds.\n");
        return -1; 
    }

    struct Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

void display(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct LinkedList* list) {
    struct Node* current = list->head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    free(list);
}

int main() {
    struct LinkedList* myList = initializeLinkedList();

    add(myList, 10);
    add(myList, 20);
    add(myList, 30);
    add(myList, 40);

    printf("Initial list: ");
    display(myList);
    printf("Size: %d\n", size(myList));

    insert(myList, 2, 25);
    printf("After inserting 25 at index 2: ");
    display(myList);

    removeAt(myList, 1);
    printf("After removing element at index 1: ");
    display(myList);

    set(myList, 2, 35);
    printf("After setting element at index 2 to 35: ");
    display(myList);

    printf("Element at index 3: %d\n", get(myList, 3));

    freeList(myList);

    return 0;
}

