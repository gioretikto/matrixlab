#include "functions.h"

void calculate(struct m *matrix, struct operator *op){
    
    int i;
     
    for(i=0; i < op->nop; i++){ 
        /*Transpose the matrices */
        if(op->symbol[i] == 't' || op->symbol[i] == 'T')
            transpose(&matrix[0]);
        
        else if(op->symbol[i] == 'd'){
			matrix[i].data[0] = determinant(matrix[i].row, &matrix[i]);
            matrix[i].row = 1;
			matrix[i].col = 1;
        }
        
        if(op->symbol[i] == 'i'){
            if(matrix[0].row != matrix[0].col)
              fprintf(stderr, "Error: You can only calculate the inverse of square matrices\n");
            inverse(matrix[0].row, &matrix[0]);
        }        
    }
    
    for(i=0; i <= op->nop; i+=2)
    {        
        if (op->symbol[i] == '+' && op->symbol[i+1] == '?'){
			struct m tmp = add(&matrix[i],&matrix[i+1],+1);
			free(matrix[i+1].data);
			matrix[i+1] = tmp;
            break;
         }
         
        if (op->symbol[i] == '-' && op->symbol[i+1] == '?'){
			struct m tmp = add(&matrix[i],&matrix[i+1],-1);
			free(matrix[i+1].data);
			matrix[i+1] = tmp;
            break;
         }
         
        if(op->symbol[i] == '*' && op->symbol[i+1] == '?'){
             if (matrix[i].row == 1 && matrix[i].col == 1)
                 scalar_product(matrix[i].data[0], &matrix[i+1]);  /* Multiplication of Scalar per matrix */
             else{
				struct m tmp = multiply(&matrix[i], &matrix[i+1]);
				free(matrix[i+1].data);
				matrix[i+1] = tmp;	
             }
             break;
         }
       
         else if(op->symbol[i] == '*' && op->symbol[i+1] == '+'){
             if (matrix[i].row == 1 && matrix[i].col == 1)
                 scalar_product(matrix[i].data[0],&matrix[i+1]);    /* Multiplication of Scalar per matrix*/
             else{
             	 struct m tmp = multiply(&matrix[i], &matrix[i+1]);
             	 free(matrix[i+1].data);
             	 matrix[i+1] = tmp;
             	 
             	 tmp = add(&matrix[i+1],&matrix[i+2],+1);
			 	 free(matrix[i+2].data);
			 	 matrix[i+2] = tmp;
             }
        }
        
          else if(op->symbol[i] == '*' && op->symbol[i+1] == '*'){
             if (matrix[i].row == 1 && matrix[i].col == 1)
                 scalar_product(matrix[i].data[0],&matrix[i+1]);    /* Multiplication of Scalar per matrix*/
             else{
             	 struct m tmp = multiply(&matrix[i], &matrix[i+1]);
             	 free(matrix[i+1].data);
             	 matrix[i+1] = tmp;
             	 
             	 tmp = multiply(&matrix[i+1],&matrix[i+2]);
			 	 free(matrix[i+2].data);
			 	 matrix[i+2] = tmp;
             }
        }
            
         else if (op->symbol[i] == '+' && op->symbol[i+1] == '*'){
			struct m tmp = multiply(&matrix[i+1], &matrix[i+2]);
			free(matrix[i+1].data);
			matrix[i+1] = tmp;

			tmp = add(&matrix[i],&matrix[i+1],+1);
			free(matrix[i+2].data);
	        matrix[i+2] = tmp;
         }

         else if (op->symbol[i] == '+' && op->symbol[i+1] == '+'){
			 struct m tmp = add(&matrix[i],&matrix[i+1],+1);
			 free(matrix[i+1].data);
			 matrix[i+1] = tmp;

			 tmp = add(&matrix[i+1],&matrix[i+2],+1);
			 free(matrix[i+2].data);
			 matrix[i+2] = tmp;			 
         }
         
         else if (op->symbol[i] == '-' && op->symbol[i+1] == '*'){
			struct m tmp = multiply(&matrix[i+1], &matrix[i+2]);
			free(matrix[i+1].data);
			matrix[i+1] = tmp;

			tmp = add(&matrix[i],&matrix[i+1],-1);
			free(matrix[i+2].data);
	        matrix[i+2] = tmp;
         }
    }
    
    printf("=\n");
    print_matrix(&matrix[op->id]); /*Print the result */
	for(i=0; i <= op->id; i++)
	 	free(matrix[i].data);
}