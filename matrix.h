#ifndef _MATRIXLAB_MATRIX_H_
#define _MATRIXLAB_MATRIX_H_

#include <stdbool.h>
#include <stdlib.h>

struct m {
    size_t row;
    size_t col;
    double *data;
};

static inline struct m *matrix_new(struct m *M, size_t r, size_t c)
{
	double *t;

	t = malloc(sizeof(double) * r * c);
	if (t == NULL)
		abort();

	M->data = t;
	M->row = r;
	M->col = c;

	return M;
}

static inline void matrix_free(struct m *M)
{
	free(M->data);
}

static inline size_t matrix_rows(struct m *M)
{
	return M->row;
}

static inline size_t matrix_cols(struct m *M)
{
	return M->col;
}

static inline double matrix_get(struct m *M, size_t r, size_t c)
{
	if (r >= M->row || c >= M->col)
		abort();

	return M->data[r * M->col + c];
}

static inline void matrix_set(struct m *M, size_t r, size_t c, double v)
{
	if (r >= M->row || c >= M->col)
		abort();

	M->data[r * M->col + c] = v;
}

static inline bool matrix_is_square(struct m *M)
{
	return M->row == M->col;
}

struct m add(const struct m *A, const struct m *B, double n);
struct m multiply(const struct m *A, const struct m *B);
void print_matrix(struct m *A);
void transpose(struct m *A);
double determinant(struct m *A);
void scalar_product(double scalar, struct m *B);
void inverse(struct m *A);

#endif /* _MATRIXLAB_MATRIX_H_ */
