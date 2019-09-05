#include "matrix.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAXNOP 20               /* Max number of operations allowed */
#define MAXNMATR 40             /* Max number of matrices */
#define MAXLINE 500             /* Max lenght of a line */

#define IN_PLACE(op, pelem) do {		\
	tmp = op(pelem);			\
	matrix_free(pelem);			\
	*pelem = tmp;				\
    } while (0)

#define IN_PLACE_1(op, pelem, arg) do {		\
	tmp = op(pelem, arg);			\
	matrix_free(pelem);			\
	*pelem = tmp;				\
    } while (0)

static void calculate(struct m *matrix, int nop, int id, char *op)
{

    int i;
    struct m tmp;

    for (i = 0; i < nop; i++) {
        /*Transpose the matrices */
        if (op[i] == 't' || op[i] == 'T')
	    IN_PLACE(transpose, &matrix[0]);

        else if (op[i] == 'd') {
            matrix[i].data[0] = determinant(&matrix[i]);
            matrix[i].row = 1;
            matrix[i].col = 1;
        }

        if (op[i] == 'i') {
            if (matrix[0].row != matrix[0].col)
                printf
                    ("Error: You can only calculate the inverse of square matrices\n");
	    IN_PLACE(inverse, &matrix[0]);
        }
    }

    for (i = 0; i <= nop; i += 2) {
        if (op[i] == '+' && op[i + 1] == '?') {
            tmp = add(&matrix[i], &matrix[i + 1], +1);
            free(matrix[i + 1].data);
            matrix[i + 1] = tmp;
            break;
        }

        else if (op[i] == '*' && op[i + 1] == '?') {
            if (matrix[i].row == 1 && matrix[i].col == 1)
		/* Multiplication of Scalar per matrix */
		IN_PLACE_1(scalar_product, &matrix[i + 1], matrix[i].data[0]);
            else {
                tmp = multiply(&matrix[i], &matrix[i + 1]);
                free(matrix[i + 1].data);
                matrix[i + 1] = tmp;
            }
            break;
        }

        else if (op[i] == '-' && op[i + 1] == '?') {
            tmp = add(&matrix[i], &matrix[i + 1], -1);
            free(matrix[i + 1].data);
            matrix[i + 1] = tmp;
            break;
        }

        else if (op[i] == '*' && op[i + 1] == '+') {
            if (matrix[i].row == 1 && matrix[i].col == 1)
		/* Multiplication of Scalar per matrix */
		IN_PLACE_1(scalar_product, &matrix[i + 1], matrix[i].data[0]);
            else {
                matrix[i + 1] = multiply(&matrix[i], &matrix[i + 1]);
                matrix[i + 2] = add(&matrix[i + 1], &matrix[i + 2], +1);
            }
        }

        else if (op[i] == '+' && op[i + 1] == '*') {
            tmp = multiply(&matrix[i + 1], &matrix[i + 2]);
            free(matrix[i + 1].data);
            matrix[i + 1] = tmp;

            tmp = add(&matrix[i], &matrix[i + 1], +1);
            free(matrix[i + 2].data);
            matrix[i + 2] = tmp;
        }

        else if (op[i] == '+' && op[i + 1] == '+') {
            tmp = add(&matrix[i], &matrix[i + 1], +1);
            free(matrix[i + 1].data);
            matrix[i + 1] = tmp;

            tmp = add(&matrix[i], &matrix[i + 2], +1);
            free(matrix[i + 2].data);
            matrix[i + 2] = tmp;
        }

        else if (op[i] == '-' && op[i + 1] == '*') {
            tmp = multiply(&matrix[i + 1], &matrix[i + 2]);
            free(matrix[i + 1].data);
            matrix[i + 1] = tmp;

            tmp = add(&matrix[i], &matrix[i + 1], -1);
            free(matrix[i + 2].data);
            matrix[i + 2] = tmp;
        }
    }

    printf("=\n");
    print_matrix(&matrix[id]);  /*Print the result */
}

void read_file(int maxc, FILE *fp)
{
    struct m matrix[MAXNMATR];
    int id;                     /* id of a matrix */
    size_t ncol, nrow;          /* No of columns of a matrix */
    int nop = 0;                /* No of operators */
    int off = 0;
    int i;
    int n;
    double *d;
    char buf[MAXLINE];          /* to store each lines of file */
    char op[MAXNOP];

    for (i = 0; i < MAXNOP; i++)
        op[i] = '?';

    ncol = 0;
    nrow = 0;
    id = 0;

    while (fgets(buf, MAXLINE, fp)) {

        if (nrow == 0) {
            /* allocate/validate max no. of matrix */
            d = matrix[id].data = malloc(sizeof(double) * maxc);
        }

        if (strcmp(buf, "^-1\n") == 0) {
            op[nop++] = 'i';    /* matrix inverse operation */
            continue;
        }

        if (strcmp(buf, "^T\n") == 0 || strcmp(buf, "^t\n") == 0) {
            op[nop++] = 't';    /* matrix inverse operation */
            continue;
        }

        if (strcmp(buf, "det\n") == 0) {
            op[nop++] = 'd';    /* determinant operation */
            continue;
        }

        /* check if line contains operator */
        if ((!isdigit(*buf) && buf[1] == '\n')) {
            op[nop++] = *buf;
            matrix[id].col = ncol;
            matrix[id].row = nrow;
            nrow = ncol = 0;
            id++;
            continue;
        }

        /* read numbers in a line into d */
	while (sscanf(buf + off, "%lf%n", d, &n) == 1) {
	    d++;
	    if (nrow == 0)
		ncol++;
	    off += n;
	}

	nrow++;
	off = 0;
    } /* end of while fgets cycle */

    fclose(fp);

    /* Assign last matrix No of columns and rows */
    matrix[id].col = ncol;
    matrix[id].row = nrow;

    if (nop == 0) {
	fprintf(stderr, "Nothing to do\n");
        exit(1);
    }

    /* Printing the matrices and operations */
    for (i = 0; i <= id; i++) {

        if (op[i] == 'd') {
            printf("det\n");
            print_matrix(&matrix[i]);
	    continue;
        }

        if (op[i] == '*' || op[i] == '-' || op[i] == '+') {
            print_matrix(&matrix[i]);
            if (op[i - 1] == 'i' || op[i - 1] == 'T' || op[i - 1] == 't')
                continue;
            else
                printf("%c\n", op[i]);
	    continue;
        }

        if (op[i] == 't' || op[i] == 'T') {
            print_matrix(&matrix[i]);
            printf("^T\n");
            if (op[i + 1] != '?')
                printf("%c\n", op[i + 1]);
	    continue;
        }

        if (op[i] == 'i') {
            print_matrix(&matrix[i]);
            printf("^-1\n");    /* matrix inverse operation */
            if (op[i + 1] != '?')
                printf("%c\n", op[i + 1]);
	    continue;
        }

        if (op[i] == '?') {
            print_matrix(&matrix[i]);
        }
    }

    calculate(matrix, nop, id, op);

    for (i = 0; i <= id; i++)
        free(matrix[i].data);
}
