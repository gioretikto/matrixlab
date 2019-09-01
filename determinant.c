#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

double determinant(size_t n, struct m *A)
{                                    
    size_t i,j,i_count,j_count, count=0;
    
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
            //Creating array of Minors
            i_count = 0;
            for(i = 1; i < n; i++)
            {
                j_count=0;
                for(j = 0; j < n; j++)
                {
                    if(j == count)
                        continue; // don't copy the minor column element
                    C.data[i_count * C.col + j_count] = A->data[i * A->col + j];
                    j_count++;
                }
                i_count++;
            }
            det += pow(-1, count) * A->data[count] * determinant(n-1,&C);//Recursive call
        }
        free(C.data);
        return det;
    }
}
