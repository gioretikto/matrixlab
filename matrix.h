#ifndef _MATRIXLAB_MATRIX_H_
#define _MATRIXLAB_MATRIX_H_

#include <stdlib.h>

struct m {
    size_t row;
    size_t col;
    double *data;
};

struct m add(const struct m *A, const struct m *B, double n);
struct m multiply(const struct m *A, const struct m *B);
void print_matrix(struct m *A);
void transpose(struct m *A);
double determinant(size_t n, struct m *A);
void scalar_product(double scalar, struct m *B);
void inverse(size_t n, struct m *A);

#endif /* _MATRIXLAB_MATRIX_H_ */
