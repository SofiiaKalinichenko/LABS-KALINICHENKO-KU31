#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    size_t capacity;
    size_t size;
} ArrayList;

void initArrayList(ArrayList* list, size_t capacity) {
    list->array = (int*)malloc(capacity * sizeof(int));
    list->capacity = capacity;
    list->size = 0;
}

void add(ArrayList* list, int item) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
    }
    list->array[list->size++] = item;
}

void insert(ArrayList* list, size_t index, int item) {
    if (index >= 0 && index <= list->size) {
        if (list->size == list->capacity) {
            list->capacity *= 2;
            list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
        }

        for (size_t i = list->size; i > index; --i) {
            list->array[i] = list->array[i - 1];
        }

        list->array[index] = item;
        list->size++;
    }
}

size_t size(const ArrayList* list) {
    return list->size;
}

void removeAt(ArrayList* list, size_t index) {
    if (index >= 0 && index < list->size) {
        for (size_t i = index; i < list->size - 1; ++i) {
            list->array[i] = list->array[i + 1];
        }

        list->size--;

        if (list->size < list->capacity / 2) {
            list->capacity /= 2;
            list->array = (int*)realloc(list->array, list->capacity * sizeof(int));
        }
    }
}

void set(ArrayList* list, size_t index, int item) {
    if (index >= 0 && index < list->size) {
        list->array[index] = item;
    }
}

int get(const ArrayList* list, size_t index) {
    if (index >= 0 && index < list->size) {
        return list->array[index];
    }
    return -1;  
}

void destroyArrayList(ArrayList* list) {
    free(list->array);
    list->array = NULL;
    list->capacity = 0;
    list->size = 0;
}

int main() {
    ArrayList list;
    initArrayList(&list, 5);

    add(&list, 10);
    add(&list, 20);
    add(&list, 30);
    add(&list, 40);

    printf("Size of the array list: %zu\n", size(&list));

    printf("Array elements: ");
    for (size_t i = 0; i < size(&list); ++i) {
        printf("%d ", get(&list, i));
    }
    printf("\n");

    insert(&list, 2, 25);

    printf("Size of the array list after insertion: %zu\n", size(&list));

    printf("Array elements after insertion: ");
    for (size_t i = 0; i < size(&list); ++i) {
        printf("%d ", get(&list, i));
    }
    printf("\n");

    removeAt(&list, 1);

    printf("Size of the array list after removal: %zu\n", size(&list));

    printf("Array elements after removal: ");
    for (size_t i = 0; i < size(&list); ++i) {
        printf("%d ", get(&list, i));
    }
    printf("\n");

    set(&list, 0, 5);

    printf("Array elements after modification: ");
    for (size_t i = 0; i < size(&list); ++i) {
        printf("%d ", get(&list, i));
    }
    printf("\n");

    destroyArrayList(&list);

    return 0;
}

