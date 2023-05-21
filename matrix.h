#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stddef.h>
typedef struct _Matrix
{
    size_t rows, cols;
    double *data;
} Matrix;

void errorProcess(char *msg, char *details);
void showMatrix(const Matrix *matrix);
Matrix *createMatrixEmpty(const int rows, const int cols);
Matrix *createMatrix(const int rows, const int cols, const double value);
Matrix *createMatrixZeros(const int rows, const int cols);
Matrix *createMatrixOnes(const int rows, const int cols);
Matrix *createMatrixRnd(const int rows, const int cols);
double drand(const int start, const int end);
void checkSubMatrix(Matrix *matrix, int row_id1, int col_id1, int row_id2, int col_id2);
Matrix *getSubMatrix(Matrix *matrix, int row_id1, int col_id1, int row_id2, int col_id2);
void deleteMatrix(Matrix **matrix);
#endif