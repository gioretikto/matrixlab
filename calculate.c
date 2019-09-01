#include "functions.h"

void calculate(struct m *matrix, int nop, int id, char *op){
    
    int i;
     
    for(i=0; i < nop; i++){ 
        /*Transpose the matrices */
        if(op[i] == 't' || op[i] == 'T')
            transpose(&matrix[0]);
        
        else if(op[i]=='d'){
            matrix[i].data[0] = determinant(matrix[i].row, &matrix[i]);
            matrix[i].row = 1;
            matrix[i].col = 1;
        }
        
        if(op[i] == 'i'){
            if(matrix[0].row != matrix[0].col)
              printf("Error: You can only calculate the inverse of square matrices\n");
            inverse(matrix[0].row, &matrix[0]);
        }        
    }
    
    for(i=0; i <= nop; i+=2)
    {        
        if (op[i] == '+' && op[i+1] == '?'){
            matrix[i+1] = add(&matrix[i],&matrix[i+1],+1);
            break;
         }
         
         else if(op[i] == '*' && op[i+1] == '?'){
             if (matrix[i].row == 1 && matrix[i].col == 1)
                 scalar_product(matrix[i].data[0], &matrix[i+1]); //Multiplication of Scalar per matrix
             else{                 
                 matrix[i+1] = multiply(&matrix[i],&matrix[i+1]);
                 matrix[i+2] = multiply(&matrix[i+1],&matrix[i+2]);
             }
             break;
         }
         
         else if (op[i] == '-' && op[i+1] == '?'){
            matrix[i+1] = add(&matrix[i],&matrix[i+1],-1);
            break;
         }
       
         else if(op[i] == '*' && op[i+1] == '+'){
             if (matrix[i].row == 1 && matrix[i].col == 1)
                 scalar_product(matrix[i].data[0],&matrix[i+1]); //Multiplication of Scalar per matrix
             else{                 
                 matrix[i+1] = multiply(&matrix[i],&matrix[i+1]);
                 matrix[i+2] = add(&matrix[i+1],&matrix[i+2],+1);
             }
        }
            
         else if (op[i] == '+' && op[i+1] == '*'){
             matrix[i+1] = multiply(&matrix[i],&matrix[i+2]);
             matrix[i+2] = add(&matrix[i],&matrix[i+1],+1);
         }
         
         else if (op[i] == '-' && op[i+1] == '*'){
            matrix[i+1] = multiply(&matrix[i],&matrix[i+2]);
            matrix[i+2] = add(&matrix[i],&matrix[i+1],-1);
         }
    }
    
    printf("=\n");
    print_matrix(&matrix[id]); /*Print the result */
    free(matrix);
}
