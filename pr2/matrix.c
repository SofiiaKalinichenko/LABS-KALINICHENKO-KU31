#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix createMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (double *)malloc(cols * sizeof(double));
    }

    return mat;
}

void freeMatrix(Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
}

void resizeMatrix(Matrix *mat, int newRows, int newCols) {
    mat->data = (double **)realloc(mat->data, newRows * sizeof(double *));
    for (int i = 0; i < newRows; i++) {
        mat->data[i] = (double *)realloc(mat->data[i], newCols * sizeof(double));
    }

    mat->rows = newRows;
    mat->cols = newCols;
}

int getRowCount(const Matrix *mat) {
    return mat->rows;
}

int getColCount(const Matrix *mat) {
    return mat->cols;
}

void setElement(Matrix *mat, int row, int col, double value) {
    mat->data[row][col] = value;
}

double getElement(const Matrix *mat, int row, int col) {
    return mat->data[row][col];
}

void printMatrix(const Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%.2f\t", mat->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix mat = createMatrix(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            setElement(&mat, i, j, i * 3 + j + 1);
        }
    }

    printf("Original Matrix:\n");
    printMatrix(&mat);

    resizeMatrix(&mat, 2, 4);

    printf("\nResized Matrix:\n");
    printMatrix(&mat);

    freeMatrix(&mat);

    return 0;
}

