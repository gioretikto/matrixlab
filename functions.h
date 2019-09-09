#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAXNOP 20 				/*Max number of operations allowed */
#define MAXNMATR 40 			/*Max number of matrices */
#define MAXLINE 500 			/*Max lenght of a line */
#define DEFAULT_DIMENSION 100
#define DEFAULT_FILE stdin

struct m{
    size_t row;
    size_t col;
    double *data;
};

struct operator{
	 int nop;	    			/* No of operators */
     char symbol[MAXNOP];
     int id;					/* No of matrix read*/
};

void print_result(struct m *matrix, struct operator *op);
void calculate(struct m *matrix, struct operator *op);
struct m add(struct m *A, struct m *B, double n);
struct m multiply(struct m *A, struct m *B);
void f(double x);
void print_matrix(struct m *A);
void transpose(struct m *A);
double determinant(size_t n, struct m *A);
void scalar_product(double scalar, struct m *B);
void inverse(size_t n, struct m *A);
void read_file(int maxc, FILE *fp);