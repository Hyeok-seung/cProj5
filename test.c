#include "matrix.h"
int main() {
    Matrix *m1 = createMatrixRnd(5, 5);
    showMatrix(m1);
    showMatrix(getSubMatrix(m1, 2, 2, 4, 4));
    return 0;
}