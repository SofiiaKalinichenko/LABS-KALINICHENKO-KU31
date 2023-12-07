#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
    double mass;
} Point;

double distance(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main() {
    int n = 4;
    Point points[] = {
        {1.0, 2.0, 3.0},
        {3.0, 4.0, 5.0},
        {5.0, 6.0, 7.0},
        {7.0, 8.0, 9.0}
    };

    while (n > 1) {
        int minIndex = 0;
        for (int i = 1; i < n; i++) {
            if (points[i].mass < points[minIndex].mass) {
                minIndex = i;
            }
        }

        int nearestIndex = (minIndex == 0) ? 1 : 0;
        double minDistance = distance(points[minIndex], points[nearestIndex]);
        for (int i = 0; i < n; i++) {
            if (i != minIndex) {
                double d = distance(points[i], points[minIndex]);
                if (d < minDistance) {
                    minDistance = d;
                    nearestIndex = i;
                }
            }
        }

        points[nearestIndex].mass += points[minIndex].mass;

        for (int i = minIndex; i < n - 1; i++) {
            points[i] = points[i + 1];
        }

        n--;
    }

    printf("Remaining point: x=%.2f y=%.2f mass=%.2f\n", points[0].x, points[0].y, points[0].mass);

    return 0;
}

