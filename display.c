#include <stdio.h>
#include "functions.h"

void print_list(struct matrix *head) {

	if(head != NULL){
		print_list(head->next);
		print_matrix(head);
		printf("\n");
	}
}

void print_matrix(struct matrix *A) {
    
     size_t i, j;

     double *tmp = A->data;
     
     if(A->op[0] == 'd')
     	printf("det\n");
     
     for(i=0; i < A->row; i++){
        for(j=0; j < A->col; j++){
                f(*(tmp++));
        }
        putchar('\n');
    }
    
    if(A->op[1] == 'i'){
    	printf("^-1\n");
 	}
 	
 	if(A->op[3] == 't')
 		printf("^T\n");
 	
	if(A->op[2] == '*' || A->op[2] == '+' || A->op[2] == '-')
		putchar(A->op[2]);
}