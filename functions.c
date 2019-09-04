#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

struct m multiply(const struct m *A, const struct m *B)
{
    size_t i, j, k;
    struct m C;
    C.data = malloc(sizeof(double) * A->row * B->col);

    C.row = A->row;
    C.col = B->col;

    for (i = 0; i < C.row; i++)
        for (j = 0; j < C.col; j++)
            C.data[i * C.col + j] = 0;

    // Multiplying matrix A and B and storing in C.
    for (i = 0; i < A->row; ++i)
        for (j = 0; j < B->col; ++j)
            for (k = 0; k < A->col; ++k)
                C.data[i * C.col + j] +=
                    A->data[i * A->col + k] * B->data[k * B->col + j];

    return C;
}

struct m add(const struct m *A, const struct m *B, double n)
{
    if ((A->row != B->row) || (A->col != B->col)) {
        printf("Error: You can't sum up matrix of different dimension\n");
        exit(1);
    }

    size_t i, j;

    struct m C;
    C.data = malloc(sizeof(double) * A->row * B->col);
    C.row = A->row;
    C.col = A->col;

    for (i = 0; i < C.row; i++)
        for (j = 0; j < C.col; j++)
            C.data[i * C.col + j] =
                A->data[i * A->col + j] + n * B->data[i * B->col + j];

    return C;
}

void f(double x)
{
    double i, f = modf(x, &i);

    if (f < .00001)
        printf("%.f ", i);

    else
        printf("%f ", x);
}

/*printing a Matrix*/

void print_matrix(struct m *A)
{

    size_t i, j;

    double *tmp = A->data;

    for (i = 0; i < A->row; i++) {
        for (j = 0; j < A->col; j++) {
            f(*(tmp++));
        }
        putchar('\n');
    }
}

void scalar_product(double scalar, struct m *B)
{
    size_t i, j;

    for (i = 0; i < B->row; i++)
        for (j = 0; j < B->col; j++)
            B->data[i * B->col + j] = scalar * B->data[i * B->col + j];
}

void transpose(struct m *A)
{
    struct m C;
    C.data = malloc(sizeof(double) * A->row * A->col);

    C.row = A->col;
    C.col = A->row;

    size_t i, j;
    for (i = 0; i < C.row; i++)
        for (j = 0; j < C.col; j++)
            C.data[i * C.col + j] = A->data[j * A->col + i];
    *A = C;
}
