#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix createMatrix(int rows, int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = (double **)malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
        matrix.data[i] = (double *)malloc(cols * sizeof(double));
    }
    return matrix;
}

void deleteMatrix(Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
}

Matrix resizeMatrix(Matrix *matrix, int newRows, int newCols) {
    Matrix newMatrix = createMatrix(newRows, newCols);
    int minRows = (matrix->rows < newRows) ? matrix->rows : newRows;
    int minCols = (matrix->cols < newCols) ? matrix->cols : newCols;

    for (int i = 0; i < minRows; i++) {
        for (int j = 0; j < minCols; j++) {
            newMatrix.data[i][j] = matrix->data[i][j];
        }
    }

    deleteMatrix(matrix);
    *matrix = newMatrix;

    return newMatrix;
}

int getRowCount(Matrix matrix) {
    return matrix.rows;
}

int getColCount(Matrix matrix) {
    return matrix.cols;
}

void setElement(Matrix *matrix, int row, int col, double value) {
    if (row >= 0 && row < matrix->rows && col >= 0 && col < matrix->cols) {
        matrix->data[row][col] = value;
    } else {
        printf("Помилка: спроба встановити значення за межами матриці.\n");
    }
}

double getElement(Matrix matrix, int row, int col) {
    if (row >= 0 && row < matrix.rows && col >= 0 && col < matrix.cols) {
        return matrix.data[row][col];
    } else {
        printf("Помилка: спроба отримати значення за межами матриці.\n");
        return 0.0;
    }
}

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%.2f\t", matrix.data[i][j]);
        }
        printf("\n");
    }
}

void saveMatrixToFile(Matrix matrix, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "%d %d\n", matrix.rows, matrix.cols);
        for (int i = 0; i < matrix.rows; i++) {
            for (int j = 0; j < matrix.cols; j++) {
                fprintf(file, "%.2f ", matrix.data[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("Матрицю збережено в файл %s\n", filename);
    } else {
        printf("Помилка відкриття файлу для запису.\n");
    }
}

Matrix readMatrixFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        int rows, cols;
        fscanf(file, "%d %d", &rows, &cols);
        Matrix matrix = createMatrix(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                fscanf(file, "%lf", &matrix.data[i][j]);
            }
        }
        fclose(file);
        printf("Матрицю зчитано з файлу %s\n", filename);
        return matrix;
    } else {
        printf("Помилка відкриття файлу для читання.\n");
        return createMatrix(0, 0);
    }
}

Matrix addMatrices(Matrix matrix1, Matrix matrix2) {
    if (matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols) {
        Matrix result = createMatrix(matrix1.rows, matrix1.cols);
        for (int i = 0; i < matrix1.rows; i++) {
            for (int j = 0; j < matrix1.cols; j++) {
                result.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
            }
        }
        return result;
    } else {
        printf("Помилка: неможливо додати матриці різних розмірів.\n");
        return createMatrix(0, 0);
    }
}

Matrix subtractMatrices(Matrix matrix1, Matrix matrix2) {
    if (matrix1.rows == matrix2.rows && matrix1.cols == matrix2.cols) {
        Matrix result = createMatrix(matrix1.rows, matrix1.cols);
        for (int i = 0; i < matrix1.rows; i++) {
            for (int j = 0; j < matrix1.cols; j++) {
                result.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];
            }
        }
        return result;
    } else {
        printf("Помилка: неможливо відняти матриці різних розмірів.\n");
        return createMatrix(0, 0);
    }
}

Matrix multiplyMatrixByScalar(Matrix matrix, double scalar) {
    Matrix result = createMatrix(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            result.data[i][j] = matrix.data[i][j] * scalar;
        }
    }
    return result;
}

Matrix multiplyMatrices(Matrix matrix1, Matrix matrix2) {
    if (matrix1.cols == matrix2.rows) {
        Matrix result = createMatrix(matrix1.rows, matrix2.cols);
        for (int i = 0; i < matrix1.rows; i++) {
            for (int j = 0; j < matrix2.cols; j++) {
                result.data[i][j] = 0;
                for (int k = 0; k < matrix1.cols; k++) {
                    result.data[i][j] += matrix1.data[i][k] * matrix2.data[k][j];
                }
            }
        }
        return result;
    } else {
        printf("Помилка: неможливо помножити матриці з такими розмірами.\n");
        return createMatrix(0, 0);
    }
}

int main() {
    Matrix matrix1 = createMatrix(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrix1.data[i][j] = i * 3 + j + 1;
        }
    }

    printf("Матриця 1:\n");
    printMatrix(matrix1);

    resizeMatrix(&matrix1, 2, 2);

    printf("\nМатриця 1 після зміни розмірів:\n");
    printMatrix(matrix1);

    Matrix matrix2 = createMatrix(2, 2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            matrix2.data[i][j] = (i + 1) * 0.5 + (j + 1) * 0.25;
        }
    }

    printf("\nМатриця 2:\n");
    printMatrix(matrix2);

    Matrix sum = addMatrices(matrix1, matrix2);
    printf("\nСума матриць 1 і 2:\n");
    printMatrix(sum);

    Matrix scaledMatrix = multiplyMatrixByScalar(matrix1, 2.0);
    printf("\nМатриця 1, помножена на 2.0:\n");
    printMatrix(scaledMatrix);

    Matrix product = multiplyMatrices(matrix1, matrix2);
    printf("\nДобуток матриць 1 і 2:\n");
    printMatrix(product);

    Matrix subtractedMatrix = subtractMatrices(matrix1, matrix2);
    printf("\nРізниця матриць 1 і 2:\n");
    printMatrix(subtractedMatrix);

    saveMatrixToFile(matrix1, "matrix1.txt");

    Matrix matrixFromFile = readMatrixFromFile("matrix1.txt");

    printf("\nМатриця, зчитана з файлу:\n");
    printMatrix(matrixFromFile);

    deleteMatrix(&matrix1);
    deleteMatrix(&sum);
    deleteMatrix(&scaledMatrix);
    deleteMatrix(&product);
    deleteMatrix(&subtractedMatrix);
    deleteMatrix(&matrixFromFile);

    printf("\nПеревірка функцій:\n");

    printf("Матриця 2:\n");
    printMatrix(matrix2);

    printf("\nКількість рядків матриці 2: %d\n", getRowCount(matrix2));
    printf("Кількість стовбців матриці 2: %d\n", getColCount(matrix2));

    setElement(&matrix2, 0, 0, 10.0);
    printf("Елемент (0,0) матриці 2: %.2f\n", getElement(matrix2, 0, 0));

    printf("\nМатриця 2:\n");
    printMatrix(matrix2);

    deleteMatrix(&matrix2);

    return 0;
}


