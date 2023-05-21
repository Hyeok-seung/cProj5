#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const char *printFmt = "%.3f\t";
const int drandStart = -10;
const int drandEnd = 10;
void errorProcess(char *msg, char *details)
{
    printf("error: [%s] %s.\n", msg, details);
}
void showMatrix(const Matrix *matrix)
{
    if (matrix == NULL)
    {
        errorProcess("Illegal Matrix Access",
                     "Matrix does not exist or has been deleted");
        return;
    }

    printf("MatrixSize = [%zu, %zu]\n", matrix->rows, matrix->cols);
    for (size_t i = 1; i <= matrix->rows; i++)
    {
        for (size_t j = 1; j <= matrix->cols; j++)
            printf(printFmt,
                   matrix->data[(size_t)(i - 1) * matrix->cols + j - 1]);
        printf("\n");
    }
}

Matrix *createMatrixEmpty(const int rows, const int cols)
{
    if (rows <= 0)
    {
        errorProcess("Illegal Matrix Definition",
                     "The number of rows is not a positive number");
        return NULL;
    }
    else if (cols <= 0)
    {
        errorProcess("Illegal Matrix Definition",
                     "The number of cols is not a positive number");
        return NULL;
        //} else if (rows > kMatrixMaxNum || cols > kMatrixMaxNum ||
        //           (int64_t)(rows * cols) > kMatrixMaxNum) {
        //  errorProcess("Illegal Matrix Definition",
        //               "The number of matrix elements is too large");
        //  return NULL;
    }

    Matrix *new_matrix = malloc(sizeof(Matrix));
    new_matrix->rows = rows;
    new_matrix->cols = cols;
    new_matrix->data = malloc((size_t)rows * cols * sizeof(float));
    return new_matrix;
}

Matrix *createMatrix(const int rows, const int cols, const double value)
{
    Matrix *new_matrix = createMatrixEmpty(rows, cols);
    for (size_t i = 0; i < (size_t)rows * cols; i++)
    {
        new_matrix->data[i] = value;
    }
    return new_matrix;
}
Matrix *createMatrixZeros(const int rows, const int cols)
{
    return createMatrix(rows, cols, 0.0);
}
Matrix *createMatrixOnes(const int rows, const int cols)
{
    return createMatrix(rows, cols, 1.0);
}

Matrix *createMatrixRnd(const int rows, const int cols)
{
    Matrix *new_matrix = createMatrixEmpty(rows, cols);
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < (size_t)rows * cols; i++)
    {
        new_matrix->data[i] = drand(drandStart, drandEnd);
    }
    return new_matrix;
}

double drand(const int start, const int end)
{
    return (double)rand() / RAND_MAX * (end - start) + start;
}

void checkSubMatrix(Matrix *matrix, int row_id1, int col_id1, int row_id2, int col_id2)
{
    if (matrix == NULL)
    {
        errorProcess("Illegal Matrix Access",
                     "Matrix does not exist or has been deleted");
        return;
    }

    if (1 <= row_id1 && row_id1 <= matrix->rows && 1 <= row_id2 &&
        row_id2 <= matrix->rows && 1 <= col_id1 && col_id1 <= matrix->cols &&
        1 <= col_id2 && col_id2 <= matrix->cols && row_id1 <= row_id2 &&
        col_id1 <= col_id2)
        return;
    errorProcess("Illegal Matrix Access", "The matrix does not exist");
    return;
}

Matrix *getSubMatrix(Matrix *matrix, int row_id1, int col_id1, int row_id2, int col_id2){
    checkSubMatrix(matrix, row_id1, col_id1, row_id2, col_id2);
    size_t new_row = row_id2 - row_id1 + 1;
    size_t new_col = col_id2 - col_id1 + 1;
    Matrix *new_matrix = createMatrixZeros(new_row, new_col);
    size_t pos = (row_id1 - 1) * matrix->cols + col_id1 - 1;
    for (size_t i = 0; i < row_id2 - row_id1 + 1; i++) {
        for (size_t j = 0; j < col_id2 - col_id1 + 1; j++)
        {
            new_matrix->data[i * new_col + j] = matrix->data[pos];
            ++pos;
        }
        pos += matrix->cols - new_col;
    }
    return new_matrix;
}

void deleteMatrix(Matrix **matrix) {
    if (matrix == NULL) return;
    if (*matrix == NULL) return;
    free((*matrix)->data);
    free(*matrix);
    (*matrix) = NULL;
}