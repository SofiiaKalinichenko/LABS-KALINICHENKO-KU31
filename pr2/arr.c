#include <stdio.h>
#include <math.h>

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    double array[n];
    printf("Enter %d real numbers:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &array[i]);
    }

    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    double average = sum / n;

    int countAboveAverage = 0;
    for (int i = 0; i < n; i++) {
        if (array[i] > average) {
            countAboveAverage++;
        }
    }

    printf("Number of elements above average: %d\n", countAboveAverage);

    double sumOfMods = 0;
    int foundNegative = 0;
    for (int i = 0; i < n; i++) {
        if (foundNegative) {
            sumOfMods += fabs(array[i]);
        }
        if (array[i] < 0) {
            foundNegative = 1;
        }
    }

    printf("Sum of absolute values after the first negative element: %.2f\n", sumOfMods);

    return 0;
}

