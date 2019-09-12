#include <stdio.h>
#include "functions.h"

void display_data(struct m *matrix, struct operator *op){
    
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