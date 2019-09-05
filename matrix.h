#ifndef _MATRIXLAB_MATRIX_H_
#define _MATRIXLAB_MATRIX_H_

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct m {
    size_t row;
    size_t col;
    double data[];
};

static inline struct m *matrix_new(size_t r, size_t c)
{
	struct m *M;
	size_t data_size = sizeof(M->data[0]) * r * c;

	M = malloc(sizeof(*M) + data_size);
	if (M == NULL)
		abort();

	memset(M->data, 0, data_size);

	M->row = r;
	M->col = c;

	return M;
}

static inline struct m *matrix_new_data(size_t r, size_t c, double *data)
{
	struct m *M;

	M = matrix_new(r, c);
	memcpy(M->data, data, sizeof(*M->data) * r * c);
	return M;
}

static inline void matrix_free(struct m *M)
{
	if (M == NULL)
		return;
	free(M);
}

static inline size_t matrix_rows(const struct m *M)
{
	return M->row;
}

static inline size_t matrix_cols(const struct m *M)
{
	return M->col;
}

static inline double matrix_get(const struct m *M, size_t r, size_t c)
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

static inline bool matrix_is_square(const struct m *M)
{
	return M->row == M->col;
}

static inline bool matrix_is_same_size(const struct m *M1,
				       const struct m *M2)
{
	return (M1->row == M2->row) && (M1->col == M2->col);
}

static inline bool matrix_is_scalar(const struct m *M)
{
	return M->col == 1 && M->row == 1;
}

struct m *add(const struct m *A, const struct m *B, double n);
struct m *multiply(const struct m *A, const struct m *B);
void print_matrix(const struct m *A);
struct m *transpose(const struct m *A);
struct m *determinant(const struct m *A);
struct m *scalar_product(const struct m *A, double scalar);
struct m *inverse(const struct m *A);

#endif /* _MATRIXLAB_MATRIX_H_ */
