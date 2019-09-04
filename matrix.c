#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/*Calculate the inverse of a matrix */

void inverse(size_t n, struct m *A)
{
    double det;
    if ((det = determinant(n, A)) == 0) {
        printf("The matrix is singular\n");
        exit(1);
    }

    size_t i, j, i_count, j_count, count = 0;

    struct m C;                 /*The Adjoint matrix */
    C.data = malloc(sizeof(double) * n * n);

    C.row = n;
    C.col = n;
    double Rdata[(n - 1) * (n - 1)];    // remaining data values
    struct m R = { n - 1, n - 1, Rdata };   // matrix structure for them
    for (count = 0; count < n * n; count++) // Create n*n Matrix of Minors
    {
        int row = count / n, col = count % n;
        for (i_count = i = 0; i < n; i++)
            if (i != row)       // don't copy the current row
            {
                for (j_count = j = 0; j < n; j++)
                    if (j != col)   // don't copy the current column
                        Rdata[i_count * R.col + j_count++] =
                            A->data[i * A->col + j];
                i_count++;
            }
        // transpose by swapping row and column
        C.data[col * C.col + row] =
            pow(-1, (row & 1) ^ (col & 1)) * determinant(n - 1, &R) / det;
    }
    free(A->data);
    *A = C;
}

double determinant(size_t n, struct m *A)
{
    size_t i, j, i_count, j_count, count = 0;

    double det = 0;

    if (n < 1) {
        printf("Error\n");
        exit(1);
    }

    else if (n == 1)
        return A->data[0];

    else if (n == 2)
        return (A->data[0] * A->data[1 * A->col + 1] -
                A->data[0 + 1] * A->data[1 * A->col + 0]);

    else {
        struct m C;

        C.row = A->row - 1;
        C.col = A->col - 1;

        C.data = malloc(sizeof(double) * (A->row - 1) * (A->col - 1));

        for (count = 0; count < n; count++) {
            //Creating array of Minors
            i_count = 0;
            for (i = 1; i < n; i++) {
                j_count = 0;
                for (j = 0; j < n; j++) {
                    if (j == count)
                        continue;   // don't copy the minor column element
                    C.data[i_count * C.col + j_count] = A->data[i * A->col + j];
                    j_count++;
                }
                i_count++;
            }
            det += pow(-1, count) * A->data[count] * determinant(n - 1, &C);    //Recursive call
        }
        free(C.data);
        return det;
    }
}

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
