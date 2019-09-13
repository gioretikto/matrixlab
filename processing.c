#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

struct m multiply(struct m *A, struct m *B) 
{ 
    size_t i, j, k;
    struct m C;
    C.data = malloc(sizeof(double) * A->row * B->col);
 
    C.row = A->row;
    C.col = B->col;
 
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
    
    struct m C;
    C.data = malloc(sizeof(double) * A->row * B->col);
    C.row = A->row;
    C.col = A->col;
    
    for (i=0; i< C.row; i++)
      for (j=0; j < C.col; j++)
        C.data[i * C.col + j] = A->data[i * A->col + j] + n *B->data[i * B->col + j];
        
    return C;
}

void f(double x)
{
    double i, f = modf(x,&i);
    
    if(fabs(f)<.00001)
        printf("%.f ",i);
    
    else printf("%f ",x);
}

/*printing a Matrix*/

void print_matrix(struct m *A){
    
     size_t i,j;

     double *tmp = A->data;
     
     for(i=0; i < A->row; i++){
        for(j=0; j < A->col; j++){
                f(*(tmp++));
        }
        putchar('\n');
    }
}

struct m scalar_product(double scalar, struct m *A)
{
    size_t i, j;
     
    struct m C;
    C.data = malloc(sizeof(double) * A->row * A->col);
 
    C.row = A->col;
    C.col = A->row;
     
    for(i=0; i < C.row; i++)
       for(j=0; j < C.col; j++)
          C.data[i * C.col + j] = scalar * A->data[i * A->col + j];
          
    return C;
}

void transpose(struct m *A)
{ 
    struct m C;
    C.data = malloc(sizeof(double) * A->row * A->col);
 
    C.row = A->col;
    C.col = A->row;

    size_t i, j; 
    for (i = 0; i < C.row; i++) 
        for (j = 0; j < C.col; j++) 
            C.data[i * C.col + j] = A->data[j * A->col  + i];
    free(A->data);
    *A = C;
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
        struct m C;
            
        C.row = A->row-1;
        C.col = A->col-1;
            
        C.data = malloc(sizeof(double) * (A->row-1) * (A->col-1));
        
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