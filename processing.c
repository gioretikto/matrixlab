#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

struct m multiply(struct m *A, struct m *B) 
{ 
    size_t i, j, k;
    
	struct m C  = make_struct(A->row, B->col);
 
    for (i=0; i< C.row; i++)
        for (j=0; j < C.col; j++)
            C.data[i * C.col + j] = 0;
 
    /* Multiplying matrix A and B and storing in C */
    for(i = 0; i < A->row; ++i)
        for(j = 0; j < B->col; ++j)
            for(k=0; k < A->col; ++k)
              C.data[i * C.col + j] += A->data[i * A->col + k] * B->data[k * B->col + j];
            
    return C;
}

struct m add(struct m *A, struct m *B, double n) 
{ 
    if ( (A->row != B->row) || (A->col != B->col) ){
        printf("Error: You can't sum up matrix of different dimension\n");
        exit(1);
    }    
    
    size_t i, j;
    
    struct m C  = make_struct(A->row, B->col);
    
    for (i=0; i < C.row; i++)
      for (j=0; j < C.col; j++)
        C.data[i * C.col + j] = A->data[i * A->col + j] + n *B->data[i * B->col + j];
        
    return C;
}

struct m scalar_product(double scalar, struct m *A)
{
    size_t i, j;
     
    struct m C = make_struct(A->row, A->col);
     
    for(i=0; i < C.row; i++)
       for(j=0; j < C.col; j++)
          C.data[i * C.col + j] = scalar * A->data[i * A->col + j];
          
    return C;
}

struct m make_struct(size_t rows, size_t cols){

	struct m C;
    C.data = malloc(sizeof(double) * rows * cols);
 
    C.row = rows;
    C.col = cols;
	
	return C;
}

void f(double x)
{
    double i, f = modf(x,&i);
    
    if(fabs(f)<.00001)
        printf("%.f ",i);
    
    else printf("%f ",x);
}

/* printing a Matrix*/

void print_matrix(struct m *A){
    
     size_t i, j;

     double *tmp = A->data;
     
     for(i=0; i < A->row; i++){
        for(j=0; j < A->col; j++){
                f(*(tmp++));
        }
        putchar('\n');
    }
}

void transpose(struct m *A)
{ 
	struct m C  = make_struct(A->row, A->col);

    size_t i, j;
    
    for (i = 0; i < C.row; i++) 
        for (j = 0; j < C.col; j++) 
            C.data[i * C.col + j] = A->data[j * A->col  + i];
    free(A->data);
    *A = C;
}

/* Calculate the inverse of a matrix */

void inverse(size_t n, struct m *A) 
{
    double det;
    det = determinant(n, A);

    if (det == 0){
        fprintf(stderr, "The matrix is singular\n");
        exit(1);
    }
    
    size_t i, j, i_count, j_count, count = 0;
    
    struct m C  = make_struct(n, n);
    
    double Rdata[(n-1)*(n-1)];        		/* remaining data values */
    struct m R = { n-1, n-1, Rdata }; 		/* matrix structure for them */
    for (count = 0; count < n*n; count++) 	/* Create n*n Matrix of Minors */
    {
        size_t row = count/n, col = count%n;
        for (i_count = i = 0; i < n; i++)
            if (i != row)                   /* don't copy the current row*/
            {
                for (j_count = j = 0; j < n; j++)
                    if (j != col)           /* don't copy the current column */
                        Rdata[i_count*R.col+j_count++] = A->data[i*A->col+j];
                i_count++;
            }
        /* transpose by swapping row and column */
        C.data[col*C.col+row] = pow(-1, (row&1) ^ (col&1)) * determinant(n-1, &R) / det;
    }
    free(A->data);
    *A=C;
}

double determinant(size_t n, struct m *A)
{                                    
    size_t i, j, i_count, j_count, count=0;
    
    double det = 0;
 
    if(n < 1)
    {
        printf("Error\n");
        exit(1);
    }
    
    else if(n==1) return A->data[0];
    
    else if(n==2) return (A->data[0]* A->data[1 * A->col + 1] - A->data[0 + 1] * A->data[1*A->col + 0]);    
    
    else{
    
    	struct m C  = make_struct(A->row-1, A->col-1);
        
        for(count=0; count < n; count++)
        {
            /* Creating array of Minors*/
            i_count = 0;
            for(i = 1; i < n; i++)
            {
                j_count=0;
                for(j = 0; j < n; j++)
                {
                    if(j == count)
                        continue; /* don't copy the minor column element */
                    C.data[i_count * C.col + j_count] = A->data[i * A->col + j];
                    j_count++;
                }
                i_count++;
            }
            det += pow(-1, count) * A->data[count] * determinant(n-1,&C); /*Recursive call */
        }
        free(C.data);
        return det;
    }
}