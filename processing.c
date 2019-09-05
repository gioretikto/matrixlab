#include "matrix.h"

#include <ctype.h>
#include <stdbool.h>
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
		tmp = matrix[i + 1];
                matrix[i + 1] = multiply(&matrix[i], &matrix[i + 1]);
		free(tmp.data);

		tmp = matrix[i + 2];
                matrix[i + 2] = add(&matrix[i + 1], &matrix[i + 2], +1);
		free(tmp.data);
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

struct matrix_state {
    double *buf;
    size_t row;
    size_t col;
    size_t pos;
    bool started; /* matrix parsing started */
};


static void matrix_parse_init(struct matrix_state *s, int maxc)
{
    s->started = false;
    s->buf = malloc(sizeof(*s->buf) * maxc);
    if (s->buf == NULL)
	abort();
}

static void matrix_parse_row(struct matrix_state *s, char *str)
{
    size_t off = 0;
    int n;

    /* read numbers in a line into s->buf */
    while (sscanf(str + off, "%lf%n", &s->buf[s->pos], &n) == 1) {
	s->pos++;
	if (s->row == 0)
	    s->col++;
	off += n;
    }

    s->row++;
}

static void matrix_parse_start(struct matrix_state *s, char *str)
{
    s->row = 0;
    s->col = 0;
    s->pos = 0;
    s->started = true;
}

static void matrix_parse_line(struct matrix_state *s, char *str)
{
    if (!s->started)
	matrix_parse_start(s, str);
    matrix_parse_row(s, str);
}

static bool matrix_parse_end(struct matrix_state *s, struct m *M)
{
    if (!s->started)
	return false;

    matrix_new_data(M, s->row, s->col, s->buf);
    s->started = false;
    return true;
}

static bool matrix_parse_end_all(struct matrix_state *s, struct m *M)
{
    bool rc;

    rc = matrix_parse_end(s, M);
    free(s->buf);

    return rc;
}

static bool is_operator_line(char *buf)
{
    return !isdigit(*buf) && buf[1] == '\n';
}

void read_file(int maxc, FILE *fp)
{
    struct m matrix[MAXNMATR];
    int id;                     /* id of a matrix */
    int nop = 0;                /* No of operators */
    int i;
    char buf[MAXLINE];          /* to store each lines of file */
    char op[MAXNOP];
    struct matrix_state parse_state;
    struct m tmp;

    for (i = 0; i < MAXNOP; i++)
        op[i] = '?';

    matrix_parse_init(&parse_state, maxc);
    id = 0;

    while (fgets(buf, MAXLINE, fp)) {
	if (id >= MAXNMATR) {
	    fprintf(stderr, "Too much matrices, max is %d\n", MAXNMATR);
	    abort();
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

        if (!is_operator_line(buf)) {
	    matrix_parse_line(&parse_state, buf);
	} else {
	    if (matrix_parse_end(&parse_state, &tmp))
		matrix[id++] = tmp;

	    op[nop++] = *buf;
            continue;
        }

    } /* end of while fgets cycle */

    fclose(fp);

    if (matrix_parse_end_all(&parse_state, &tmp))
	matrix[id] = tmp;

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
