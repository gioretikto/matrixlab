#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "lists.h"

void add_item(struct matrix **ptr, long double *data, size_t nrow, size_t ncol, char *op);
void print_matrix(struct matrix *A);
void print_number(long double x);
void reverse(struct matrix **head_ref);
void summation(struct matrix *tmp, long double n);
void multiplication(struct matrix *head);
void delNextMatrix (struct matrix *head);
long double determinant(struct matrix *A, size_t n);
int stop(struct matrix *head, const char *error);
struct matrix *delMatrix (struct matrix *head);
void scalar_product(struct matrix *A, long double *scalar);
long double trace(struct matrix *A);
void inverse(struct matrix *A);
void transpose(struct matrix *A);

int read_file(unsigned int dim, FILE *fp)
{
	struct matrix *head = NULL;

	char op = '?';

	unsigned const int maxline = 100;

    char line[maxline]; 			/* to store each lines of file */
    char *buf = line;

	unsigned int check_dim;
	int n;
	unsigned int offset;
	size_t row, col;
    long double data[dim];
	long double *tmp_data = data;

	row = col = n = offset = check_dim = 0;

    /* Read file line by line */
    while (fgets(buf = line, maxline, fp))
	{
        if (isdigit(*buf) || (*buf == '-' && isdigit(buf[1])))
		{
			if (check_dim < dim)
			{
				while (sscanf(buf + offset, "%Lf%n", tmp_data, &n) == 1)		/* read numbers in a line into tmp_data */
				{
					if (++check_dim <= dim)
						tmp_data++;

					else
						return stop(head, "Dimension Overflow");

					if (row == 0)
						col++;
					offset += n;
				}

				row++;
				offset = 0;
			}

			else
				return stop(head, "Dimension Overflow");
		}

		else if (isalpha(*buf))			/* check for unary operator: det, inv, transpose etc */
		{
			if (row == 0 )
				return stop(head, "Write the matrix first then append the operator");

			else
			{
				add_item(&head, data, row, col, &op);
				print_matrix(head);

				if (strncmp(buf, "det", 3) == 0)
				{
					if (head != NULL)
					{
						*head->data = determinant(head, head->row);
						head->row = head->col = 1;
						printf("det\n");
						op = 'd';
					}
				}

				else if (strncmp(buf, "tr", 2) == 0)
				{
					if (head != NULL)
					{
						*head->data = trace(head);
						head->row = head->col = 1;
						printf("tr\n");
						op = 'r';
					}
				}

				else if (strncmp(buf, "inv", 3) == 0)
				{
					if(head->row != head->col)
						return stop(head, "Only square matrices are invertible");

					else{
						if (head != NULL)
						{
							inverse(head);
							printf("inv\n");
							op = 'i';
						}
					}
				}

				else if (*buf == 't')
				{
					if (head != NULL)
					{
						transpose(head);
						printf("t\n");
						op = 't';
					}
				}

				else
					return stop(head, "Syntax error");
			}
		}

        else if (!isalpha(*buf) && buf[1] == '\n')         /* check for binary operator */
		{
			if (row == 0)
				return stop(head, "Write the matrix first then append the operator");

			else
			{
				switch (*buf)
				{
					case '*':
						op = '*';
						break;

					case '+':
						op = '+';
						break;

					case '-':
						op = '-';
						break;

				    case '/':
						return stop(head, "you cannot divide matrices");
		
					default:
						return stop(head, "Invalid character");
				}

				add_item(&head, data, row, col, &op);

				print_matrix(head);

				printf("%c\n",op);

				op = '?';
				row = col = check_dim = 0;
				tmp_data = data;
			}
		}

	} /* End of line parsing */

	if (row != 0 && op == '?')
	{
		add_item(&head, data, row, col, &op);
		print_matrix(head);
	}

	fclose(fp);

	if (head != NULL)
	{
		if (head->next != NULL)
			reverse(&head);

		struct matrix *tmp = head;

		while (tmp->next != NULL)			/* Scalar product: n * matrix */
		{
			if (tmp->op == '*')
			{
				if (tmp->col == 1 && tmp->row == 1)
				{
					scalar_product(tmp->next, tmp->data);

					tmp = head = delMatrix(tmp);

				}

				else if (tmp->next->col == 1 && tmp->next->row == 1)
				{
					scalar_product(tmp, tmp->next->data);

					delNextMatrix(tmp);
				}

				else					/* it's not a scalar product n * matrix but matrix * matrix */
					tmp = tmp->next;
			}

			else
				tmp = tmp->next;
		}

		tmp = head;

		while (tmp->next != NULL)			/* Multiply matrices */
		{
			if (tmp->op == '*')
			{
				if (tmp->col != tmp->next->row)
					return stop (head, "Multiplication of matrices AB, is only defined when number of columns of A equals number of rows of B");

				else
				{
					multiplication(tmp);

					delNextMatrix(tmp);
				}
			}

			else
				tmp = tmp->next;
		}

		tmp = head;

		/* Add up all matrix */

		while (tmp->next != NULL)
		{
			if (tmp->op == '+')
			{
				summation(tmp,1);
				delNextMatrix(tmp);
			}

			else if (tmp->op == '-')
			{
				summation(tmp,-1);
				delNextMatrix(tmp);
			}

			else
				break;
		}
	
		printf("=\n");

	    print_matrix(head);		/* Print the result */
	
	    free(head->data);

	    free(head);
	}

	else
		return stop(head, "head is NULL");

	return 0;
}

void print_matrix(struct matrix *A)
{

     size_t i, j;

     long double *tmp = A->data;

     for (i = 0; i < A->row; i++)
	 {
        for (j = 0; j < A->col; j++)
			print_number(*(tmp++));

	    putchar('\n');
     }
}

void print_number(long double x)
{
 	long double tmp = ceill(x);

    if (fabsl(x-tmp) < 0.00000000001)
	{
        x = tmp;
	}

	if (x == -0)
		x = fabsl(x);
	
	printf("%.19Lg ", x);
}
