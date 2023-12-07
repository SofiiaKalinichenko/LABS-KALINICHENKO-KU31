#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Point {
    int position;
    int mass;
    bool merged;
};

int findMinMassPoint(struct Point *points, int n) {
    int minMass = -1;
    int minMassIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!points[i].merged && (minMass == -1 || points[i].mass < minMass)) {
            minMass = points[i].mass;
            minMassIndex = i;
        }
    }

    return minMassIndex;
}

int findNearestNeighbor(struct Point *points, int n, int index) {
    int nearestIndex = -1;
    int minDistance = -1;

    for (int i = 0; i < n; i++) {
        if (!points[i].merged && i != index) {
            int distance = abs(points[i].position - points[index].position);
            if (nearestIndex == -1 || distance < minDistance) {
                nearestIndex = i;
                minDistance = distance;
            }
        }
    }

    return nearestIndex;
}

void mergePoints(struct Point *points, int index1, int index2) {
    points[index2].mass += points[index1].mass;
    points[index1].mass = 0;
    points[index1].merged = true;
}

int main() {
    srand(time(NULL));

    int n;
    printf("Введіть кількість точок: ");
    scanf("%d", &n);

    struct Point *points = malloc(n * sizeof(struct Point));

    for (int i = 0; i < n; i++) {
        points[i].mass = rand() % 100 + 1;
        points[i].position = i + 1;
        points[i].merged = false;
    }

    printf("Початковий стан точок:\n");
    for (int i = 0; i < n; i++) {
        printf("Точка %d: маса %d\n", points[i].position, points[i].mass);
    }

    int remainingPoints = n;
    while (remainingPoints > 1) {
        int minMassIndex = findMinMassPoint(points, n);

        if (minMassIndex == -1) {
            break;
        }

        int nearestIndex = findNearestNeighbor(points, n, minMassIndex);

        mergePoints(points, minMassIndex, nearestIndex);

        printf("\nТочки %d і %d об'єднані. Залишилось %d точок:\n",
               points[minMassIndex].position, points[nearestIndex].position, remainingPoints - 1);

        for (int i = 0; i < n; i++) {
            if (!points[i].merged) {
                printf("Точка %d: маса %d\n", points[i].position, points[i].mass);
            }
        }

        remainingPoints--;
    }

    for (int i = 0; i < n; i++) {
        if (!points[i].merged) {
            printf("\nЗалишилася точка %d з масою %d.\n", points[i].position, points[i].mass);
            break;
        }
    }

    free(points);

    return 0;
}
