#include "functions.h"

void calculate(struct m *matrix, struct operator *op){
    
    int i;
     
    for(i=0; i < op->nop; i++){
    
    	switch(op->symbol[i]){
    		case 't':
    		case 'T':
    			transpose(&matrix[0]);
            	continue;
            case 'd':
    			matrix[i].data[0] = determinant(matrix[i].row, &matrix[i]);
				matrix[i].row = 1;
				matrix[i].col = 1;
				continue;
				
			case 'i':
				if(matrix[0].row != matrix[0].col){
		          fprintf(stderr, "Error: You can only calculate the inverse of square matrices\n");
                  exit(1);
        		}
        		else
        		  inverse(matrix[0].row, &matrix[0]);
        		continue;
        	default:
        		break;
        }        
    }
    
    for(i=0; i <= op->nop; i+=2)
    {        
    	struct m tmp;
    	
        if (op->symbol[i] == '+' && op->symbol[i+1] == '?'){
			tmp = add(&matrix[i], &matrix[i+1], op->symbol[i]);
			copy_matrix(&matrix[i+1], &tmp);
            break;
        }
         
        if (op->symbol[i] == '-' && op->symbol[i+1] == '?'){
			tmp = add(&matrix[i], &matrix[i+1], op->symbol[i]);
			copy_matrix(&matrix[i+1], &tmp);
            break;
        }
         
        if(op->symbol[i] == '*' && op->symbol[i+1] == '?'){
        
             if (matrix[i].row == 1 && matrix[i].col == 1){
                 tmp = scalar_product(matrix[i].data[0], &matrix[i+1]);  /* Multiplication of Scalar per matrix */
                 copy_matrix(&matrix[i+1], &tmp);
             }
             
             else{
				tmp = multiply(&matrix[i], &matrix[i+1]);
				copy_matrix(&matrix[i+1], &tmp);	
             }
             
             break;
        }     
         
        if(op->symbol[i] == '*' && op->symbol[i+1] == 'd' && matrix[i].row == 1 && matrix[i].col == 1){		/* Matrix1 * det(Maitrix2) or number * det(Maitrix2)*/

                 tmp = scalar_product(matrix[i].data[0], &matrix[i+1]);  /* Multiplication of Scalar per matrix */
                 copy_matrix(&matrix[i+1], &tmp);

                 if(op->symbol[i+2] == '?')
	              	  break;
              	 
    	         else if(op->symbol[i+2] == '*'){
				        tmp = scalar_product(matrix[i+1].data[0], &matrix[i+2]);  /* Multiplication of Scalar per matrix */
				        copy_matrix(&matrix[i+2], &tmp);
		              	break;
	       		 }
	       		 
	       		 else{
	       		 	printf("Matrixlab error: Wrong dimension\n");
           			break;
           		}
  		 		continue;
  		 }
  		 
         else if(op->symbol[i] == '*' && (op->symbol[i+1] == '+' || op->symbol[i+1] == '-')){   /* matrix * matrix -/+ matrix */
         
              if (matrix[i].row == 1 && matrix[i].col == 1){
                 tmp = scalar_product(matrix[i].data[0], &matrix[i+1]);  /* Multiplication of Scalar per matrix */
                 copy_matrix(&matrix[i+1], &tmp);
                 tmp = add(&matrix[i+1], &matrix[i+2], op->symbol[i+1]);
			 	 copy_matrix(&matrix[i+2], &tmp);
              }             
             
              else{
             	 tmp = multiply(&matrix[i], &matrix[i+1]);
             	 copy_matrix(&matrix[i+1], &tmp);
             	 tmp = add(&matrix[i+1], &matrix[i+2], op->symbol[i+1]);
			 	 copy_matrix(&matrix[i+2], &tmp);
              }
             
              continue;
        }
               
          else if(op->symbol[i] == '*' && op->symbol[i+1] == '*'){
          
             if (matrix[i].row == 1 && matrix[i].col == 1){
                 tmp = scalar_product(matrix[i].data[0], &matrix[i+1]);    /* Multiplication of Scalar per matrix*/
                 copy_matrix(&matrix[i+1], &tmp);
                 tmp = multiply(&matrix[i+1], &matrix[i+2]);
			 	 copy_matrix(&matrix[i+2], &tmp);
             }
             
             else{
             	 tmp = multiply(&matrix[i], &matrix[i+1]);
             	 copy_matrix(&matrix[i+1], &tmp);
             	 tmp = multiply(&matrix[i+1], &matrix[i+2]);
			 	 copy_matrix(&matrix[i+2], &tmp);
             }
             
             continue;
        }
            
         else if ((op->symbol[i] == '+' || op->symbol[i] == '-') && op->symbol[i+1] == '*'){
			tmp = multiply(&matrix[i+1], &matrix[i+2]);
			copy_matrix(&matrix[i+1], &tmp);
			tmp = add(&matrix[i], &matrix[i+1], op->symbol[i]);
			copy_matrix(&matrix[i+2], &tmp);
	        continue;
         }

         else if ((op->symbol[i] == '+' || op->symbol[i] == '-') && (op->symbol[i+1] == '+' || op->symbol[i+1] == '-')){
			 tmp = add(&matrix[i],&matrix[i+1], op->symbol[i+1]);
			 copy_matrix(&matrix[i+1], &tmp);
			 tmp = add(&matrix[i+1],&matrix[i+2], op->symbol[i+1]);
			 copy_matrix(&matrix[i+2], &tmp);
			 continue;		 
         }
    }
    
    printf("=\n");
    print_matrix(&matrix[op->id]); /*Print the result */
	
	for(i=0; i <= op->id; i++)
	 	free(matrix[i].data);
}