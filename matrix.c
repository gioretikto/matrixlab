#include "matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double determinant_int(const struct m *A)
{
    size_t i, j, i_count, j_count, count;
    double det = 0;
    double t;
    struct m *C;
    size_t n = matrix_rows(A);

    if (n < 1) {
        fprintf(stderr, "Error, matrix size < 1\n");
        exit(1);
    }

    if (n == 1)
        return matrix_get(A, 0, 0);

    if (n == 2) {
	t = matrix_get(A, 0, 0) * matrix_get(A, 1, 1)
	    - matrix_get(A, 0, 1) * matrix_get(A, 1, 0);
	return t;
    }

    C = matrix_new(matrix_cols(A) - 1, matrix_rows(A) - 1);

    for (count = 0; count < n; count++) {
	/* Creating array of Minors */
	i_count = 0;
	for (i = 1; i < n; i++) {
	    j_count = 0;
	    for (j = 0; j < n; j++) {
		if (j == count)
		    /* don't copy the minor column element */
		    continue;

		t = matrix_get(A, i, j);
		matrix_set(C, i_count, j_count, t);
		j_count++;
	    }
	    i_count++;
	}
	det += pow(-1, count) * matrix_get(A, count, 1) * determinant_int(C); /* Recursive call */
    }
    matrix_free(C);
    return det;
}

struct m *inverse(const struct m *A)
{
    double det;
    size_t n = matrix_rows(A);
    struct m *C;                 /*The Adjoint matrix */
    struct m *R;
    size_t i, j, i_count, j_count, count;
    int row;
    int col;
    double t;

    det = determinant_int(A);
    if (det == 0) {
	fprintf(stderr, "The matrix is singular\n");
        exit(1);
    }

    C = matrix_new(n, n);
    R = matrix_new(n - 1, n - 1);
    /* Create n*n Matrix of Minors */
    for (count = 0; count < n * n; count++) {
        row = count / n;
        col = count % n;

        for (i_count = i = 0; i < n; i++) {
	    /* don't copy the current row */
            if (i != row) {
                for (j_count = j = 0; j < n; j++) {
		    /* don't copy the current column */
                    if (j != col) {
			t = matrix_get(A, i, j);
                        matrix_set(R, i_count, j_count++, t);
		    }
		}
                i_count++;
            }
	}
        /* transpose by swapping row and column */
	t = pow(-1, (row & 1) ^ (col & 1)) * determinant_int(R) / det;
	matrix_set(C, col, row, t);
    }

    matrix_free(R);
    return C;
}

struct m *determinant(const struct m *A)
{
	double t;

	t = determinant_int(A);
	return matrix_new_data(1, 1, &t);
}

struct m *multiply(const struct m *A, const struct m *B)
{
    size_t i, j, k;
    struct m *C;
    size_t row, col;
    double t1, t2;

    row = matrix_rows(A);
    col = matrix_cols(B);

    C = matrix_new(col, row);

    /* Multiplying matrix A and B and storing in C */
    for (i = 0; i < row; ++i)
        for (j = 0; j < col; ++j)
            for (k = 0; k < matrix_cols(A); ++k) {

		t1 = matrix_get(A, i, k) * matrix_get(B, k, j);
		t2 = matrix_get(C, i, j);
		matrix_set(C, i, j, t1 + t2);
	    }

    return C;
}

struct m *add(const struct m *A, const struct m *B, double n)
{
    size_t i, j;
    struct m *C;
    size_t col, row;
    double t;

    if (!matrix_is_same_size(A, B)) {
        fprintf(stderr,
		"Error: You can't sum up matrix of different dimension\n");
        exit(1);
    }

    col = matrix_cols(A);
    row = matrix_rows(A);

    C = matrix_new(col, row);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
	    t = matrix_get(A, i, j) + (n * matrix_get(B, i, j));
	    matrix_set(C, i, j, t);
	}
    }

    return C;
}

static void print_elem(double x)
{
    double i, f = modf(x, &i);

    if (f < .00001)
        printf("%.f ", i);
    else
        printf("%f ", x);
}

void print_matrix(const struct m *A)
{
    size_t i, j;
    size_t row = matrix_rows(A);
    size_t col = matrix_cols(A);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
	    print_elem(matrix_get(A, i, j));
        }
        putchar('\n');
    }
}

struct m *scalar_product(const struct m *A, double scalar)
{
    size_t i, j;
    double t;
    struct m *R;
    size_t row, col;

    row = matrix_rows(A);
    col = matrix_cols(A);

    R = matrix_new(row, col);

    for (i = 0; i < row; i++) {
	for (j = 0; j < col; j++) {
	    t = scalar * matrix_get(A, i, j);
	    matrix_set(R, i, j, t);
	}
    }
    return R;
}

struct m *transpose(const struct m *A)
{
    struct m *C;
    size_t i, j;
    size_t row, col;
    double t;

    /* transpose, so opposite order */
    row = matrix_cols(A);
    col = matrix_rows(A);

    C = matrix_new(row, col);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
	    t = matrix_get(A, j, i);
	    matrix_set(C, i, j, t);
	}
    }

    return C;
}
