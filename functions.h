#include <stdlib.h>
#include <stdio.h>

#define MAXNOP 20 /*Max number of operations allowed */

struct m{
    size_t row;
    size_t col;
    double *data;
};

struct m add(struct m *A, struct m *B, double n);
struct m multiply(struct m *A, struct m *B);
void f(double x);
void print_matrix(struct m *A);
void transpose(struct m *A);
double determinant(size_t n, struct m *A);
void scalar_product(double scalar, struct m *B);
void inverse(size_t n, struct m *A);
void read_file(int maxc, FILE *fp);
void calculate(struct m *matrix, int nop, int id, char op[MAXNOP]);
