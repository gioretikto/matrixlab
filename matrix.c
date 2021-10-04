/* Matrix operation functions */

#include "lists.h"
#include <math.h>

struct matrix make_struct(size_t rows, size_t cols);

void summation(struct matrix *tmp, long double n)
{
	if ((tmp->row != tmp->next->row) || (tmp->col != tmp->next->col))
	{
		fprintf(stderr, "Matrixlab Error: You can't sum up matrix of different dimension\n");
		return;
	}

	else
	{
		size_t i, j;

		for (i = 0; i < tmp->row; i++)
		 	for (j = 0; j < tmp->col; j++)
		    	tmp->data[i * tmp->col + j] = tmp->data[i * tmp->col + j] + n * tmp->next->data[i * tmp->next->col + j];
	}
}

void multiplication(struct matrix *tmp)
{
	struct matrix C = make_struct(tmp->row, tmp->next->col);

	size_t i, j, k;

	for (i = 0; i < C.row; i++)
		for (j = 0; j < C.col; j++)
		    C.data[i * C.col + j] = 0;

	/* Multiplying matrix A and B and storing in C */
	for (i = 0; i < tmp->row; ++i)
	{
		for (j = 0; j < tmp->next->col; ++j)
			for (k = 0; k < tmp->col; ++k)
				C.data[i * C.col + j] += tmp->data[i * tmp->col + k] * tmp->next->data[k * tmp->next->col + j];
	}

	if ((tmp->row != C.row) || (tmp->col != C.col))
	{
		tmp->data = (long double *) realloc(tmp->data, sizeof(long double) * C.row * C.col);
		tmp->row = C.row;
		tmp->col = C.col;
	}

	memcpy(tmp->data, C.data, sizeof(long double) * C.row * C.col);

	free(C.data);
}

void scalar_product(struct matrix *A, long double *scalar)
{
    size_t i, j;
    
    for (i = 0; i < A->row; i++)
       for (j = 0; j < A->col; j++)
          A->data[i * A->col + j] = *scalar * A->data[i * A->col + j];
}


long double trace(struct matrix *A)
{
	long double sum = 0;

	size_t i;

	for(i = 0; i < A->row; i++)
    {
        sum = sum + A->data[i * A->col + i];   /* sum of the diagonal elements */
    }

	return sum;

}

long double determinant(struct matrix *A, size_t n)
{                                    
    size_t i, j, i_count, j_count, count = 0;
    
    long double det = 0;
 
    if (n < 1)
    {
        printf("Error\n");
        exit(1);
    }
    
    else if (n==1) return A->data[0];
    
    else if (n==2) return (A->data[0]* A->data[1 * A->col + 1] - A->data[0 + 1] * A->data[1*A->col + 0]);    
    
    else
	{    
        struct matrix C  = make_struct(A->row-1, A->col-1);
        
        for (count = 0; count < n; count++) /* Creating array of Minors*/
        {            
            i_count = 0;

            for (i = 1; i < n; i++)
            {
                j_count = 0;

                for (j = 0; j < n; j++)
                {
                    if (j == count)
                        continue; /* don't copy the minor column element */

                    C.data[i_count * C.col + j_count] = A->data[i * A->col + j];
                    j_count++;
                }

                i_count++;
            }

            det += pow(-1, count) * A->data[count] * determinant(&C, n-1); /*Recursive call */
        }

        free(C.data);

        return det;
    }
}


void transpose(struct matrix *A)
{
    struct matrix C  = make_struct(A->col, A->row);

    size_t i, j;
    
 	for (i = 0; i < C.row; i++) 
    	for (j = 0; j < C.col; j++)
        	C.data[i * C.col + j] = A->data[j * A->col  + i];
    
   memcpy(A->data, C.data, sizeof(double) * C.row * C.col);

   A->row = C.row;
   A->col = C.col; 
   free(C.data);
}

void inverse(struct matrix *A)
{
	size_t n = A->row;
		 
	double det = determinant(A, n);
		 
	if (fabs(det) < 0.0001) {
		fprintf(stderr, "The matrix is singular\n");
		exit(1);
	}
		   
	size_t i, j, i_count, j_count, count = 0;
		   
	struct matrix C  = make_struct(n, n);
		   
	long double mdata[(n-1)*(n-1)];      /* remaining data values */
		 
	struct matrix M;    /* matrix structure for them */
	M.data = mdata;
	M.row = n-1;
	M.col = n-1;
		   
	for (count = 0; count < n*n; count++)       /* Create n*n Matrix of Minors */
	{
		size_t row = count/n, col = count%n;
		for (i_count = i = 0; i < n; i++)
			if (i != row)       /* don't copy the current row*/
			{
				for (j_count = j = 0; j < n; j++)
					if (j != col)       /* don't copy the current column */
						mdata[i_count*M.col+j_count++] = A->data[i*A->col+j];
				i_count++;
			}
		/* transpose by swapping row and column */
        C.data[col*C.col+row] = powl(-1, (row&1) ^ (col&1)) * determinant(&M, n-1) / det;
		M.data = mdata;
	}
		 
	memcpy(A->data, C.data, sizeof(double) * C.row * C.col);
	free(C.data);
}
