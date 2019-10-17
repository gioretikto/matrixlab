#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define DEFAULT_FILE stdin
#define MAXLINE 500
#define MAX_DIM 20
#define VERSION "2.1"

struct matrix {
	    size_t row, col;
   	 	double *data;
		char op[4];			  /* the first element for determinant the 2nd for transpose and 3d for * + -; 4th for transpose  */
        char value;
        struct matrix *next;       /* pointer to the next item */
};

void free_all(struct matrix *head);
void read_file(int dim, FILE *fp);
void f(double x);
void print_list(struct matrix *head);
void print_matrix(struct matrix *A);
void add_item(struct matrix **ptr, double *data, size_t nrow, size_t ncol, char *op, char value);
void multiplication(struct matrix *A);
void multiply(struct matrix *A, struct matrix *B);
void scalar_product(double scalar, struct matrix *A);
void delete(struct matrix *head);
struct matrix make_struct(size_t rows, size_t cols);
void add(struct matrix *A, struct matrix *B, const char c);
void summation(struct matrix *head);
double determinant(size_t n, struct matrix *A);
void det(struct matrix *head);
void inv(struct matrix *head);
void inverse(size_t n, struct matrix *A);
void trans(struct matrix *head);
void transpose(struct matrix *A);
void remove_spaces(char* s);
struct matrix *find_node(struct matrix *head, char value);
void halt(struct matrix *head, const char *error);