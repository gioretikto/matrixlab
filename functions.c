#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

void print_result(struct m *matrix, struct operator *op){
    
    int i;
    
    /* Printing the matrices and operations */
    for(i=0; i <= op->id; i++){
                     
        if(op->symbol[i] == 'd'){
            printf("det\n");
            print_matrix(&matrix[i]);
            continue;
        }
        
        if (op->symbol[i] == '*' || op->symbol[i] == '-' || op->symbol[i] == '+')
        {
            print_matrix(&matrix[i]);
            if( i > 0 && (op->symbol[i - 1] == 'i' || op->symbol[i - 1] == 'T' || op->symbol[i - 1] == 't'))
                continue;
            else
                printf("%c\n", op->symbol[i]);
        }
        
         if (op->symbol[i] == 't' || op->symbol[i] == 'T'){            
             print_matrix(&matrix[i]);
             printf("^T\n");
             if(op->symbol[i+1] != '?')
                printf("%c\n", op->symbol[i+1]);
             continue;
        }
        
         if (op->symbol[i] == 'i'){
            print_matrix(&matrix[i]);
            printf("^-1\n"); 	/* matrix inverse operation */
            if(op->symbol[i+1] != '?')
                printf("%c\n", op->symbol[i+1]);
            continue;
        }
        
         if(op->symbol[i] == '?'){
             print_matrix(&matrix[i]);
        }        
    }
    
    calculate(matrix, op);
}


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
    double i,f= modf(x,&i);
    
    if(f<.00001)
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

void scalar_product(double scalar, struct m *B)
{
     size_t i,j;
     
     for(i=0; i < B->row; i++)
        for(j=0; j < B->col; j++)
           B->data[i * B->col + j] = scalar * B->data[i * B->col + j];
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
    *A = C;
}
