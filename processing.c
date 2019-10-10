#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "functions.h"

void f(double x)
{
    double i, r = modf(x,&i);
    
    if(fabs(r)<.00001)
        printf("%.f ",i);
    
    else printf("%f ",x);
}

void add_item(struct matrix **ptr, double *data, size_t nrow, size_t ncol, char *op, char value)
{
        struct matrix *item;

        item = malloc(sizeof(*item));

	    if (item == NULL)
        	return;
		else
			item->data = malloc(sizeof(double) * nrow * ncol);

        item->next = *ptr;

		memcpy(item->data, data, sizeof(double) * nrow * ncol);
		item->row = nrow;
		item->col = ncol;
		item->op[0] = *op;
		item->op[1] = op[1];	
		item->op[2] = op[2];
		item->op[3] = op[3];
		item->value = value;
		*ptr = item;
}

void inv(struct matrix *head) {

		if(head == NULL)
			return;

		if(head->op[1] != 'i')
			inv(head->next);

		if(head->op[1] == 'i'){
			inverse(head->row, head);
			head->op[1] = '\0';
			inv(head->next);
		}
}

void trans(struct matrix *head) {

		if(head == NULL)
			return;

		if(head->op[3] != 't')
			trans(head->next);

		if(head->op[3] == 't'){
			head->op[3] = '\0';
			transpose(head);
			trans(head->next);
		}
}

void multiplication(struct matrix *head) {

		if(head == NULL)
			return;

		else if (head->next != NULL){
		
			if((head->next)->op[2] != '*')
				multiplication(head->next);

			if((head->next)->op[2] == '*') {
				if ((head->next)->col == 1 && (head->next)->row == 1)
					scalar_product(*(head->next)->data, head);
						
				else
					multiply(head->next, head);

				delete(head);
				multiplication(head);
			}
		}
}

void summation(struct matrix *head){

		if(head == NULL)
			return;

		else if (head->next != NULL){

			if((head->next)->op[2] != '+' || (head->next)->op[2] != '-' )
				summation(head->next);

			if((head->next)->op[2] == '+' || (head->next)->op[2] == '-' ){
				add(head->next, head, (head->next)->op[2]);
				delete(head);
				summation(head);
			}
		}
}

void det(struct matrix *head){
		
		if(head == NULL)
			return;

		if(head->op[0] != 'd')
				det(head->next);

		if(head->op[0] == 'd'){
			*head->data = determinant(head->row, head);
			head->row = 1;
			head->col = 1;
			head->op[0] = '\0';
			head->data = realloc(head->data, sizeof(double));
			det(head->next);
		}
}

void multiply(struct matrix *A, struct matrix *B)
{
    size_t i, j, k;

	struct matrix C  = make_struct(A->row, B->col);

    for (i=0; i< C.row; i++)
        for (j=0; j < C.col; j++)
            C.data[i * C.col + j] = 0;
 
    /* Multiplying matrix A and B and storing in C */
    for(i = 0; i < A->row; ++i){
    	for(j = 0; j < B->col; ++j)
    	    for(k=0; k < A->col; ++k)
    	        C.data[i * C.col + j] += A->data[i * A->col + k] * B->data[k * B->col + j];
    }

	memcpy(B->data, C.data, sizeof(double) * C.row * C.col);
	B->row = C.row;
	B->col = C.col;
	free(C.data);
}

void delete(struct matrix *head) 
{
    struct matrix *temp;
    temp = head->next;
    head->next = temp->next;
    free(temp->data);
    free(temp);
}

void scalar_product(double scalar, struct matrix *A)
{
    size_t i, j;
    
	struct matrix C = make_struct(A->row, A->col);
     
    for(i=0; i < C.row; i++)
       for(j=0; j < C.col; j++)
          C.data[i * C.col + j] = scalar * A->data[i * A->col + j];

	memcpy(A->data, C.data, sizeof(double) * C.row * C.col);
	free(C.data);
}

struct matrix make_struct(size_t rows, size_t cols){

    struct matrix C;
    C.data = malloc(sizeof(double) * rows * cols);
 
    C.row = rows;
    C.col = cols;
    
    return C;
}

void add(struct matrix *A, struct matrix *B, const char c)
{ 
    if ((A->row != B->row) || (A->col != B->col)){
             printf("Matrixlab Error: You can't sum up matrix of different dimension\n");
             exit(1);
    }
    
    size_t i, j;
    
    double n = 0;
    
    if (c == '+')
        n = 1;
        
    else if (c == '-')
        n = -1;
    
    struct matrix C = make_struct(A->row, B->col);
    
    for (i=0; i < C.row; i++)
         for (j=0; j < C.col; j++)
            C.data[i * C.col + j] = A->data[i * A->col + j] + n * B->data[i * B->col + j];
        
    memcpy(B->data, C.data, sizeof(double) * C.row * C.col);
	free(C.data);
}

double determinant(size_t n, struct matrix *A)
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
    
        struct matrix C  = make_struct(A->row-1, A->col-1);
        
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
            det += pow(-1, count) * A->data[count] * determinant(n-1, &C); /*Recursive call */
        }
        free(C.data);
        return det;
    }
}

void inverse(size_t n, struct matrix *A) 
{
    double det;
    det = determinant(n, A);

    if (fabs(det) < 0.0001) {
        fprintf(stderr, "The matrix is singular\n");
        exit(1);
    }
    
    size_t i, j, i_count, j_count, count = 0;
    
    struct matrix C  = make_struct(n, n);
    
    double mdata[(n-1)*(n-1)];              /* remaining data values */
    struct matrix M;       /* matrix structure for them */
    M.data = mdata;
    M.row = n-1;
    M.col = n-1;
    
    for (count = 0; count < n*n; count++)   /* Create n*n Matrix of Minors */
    {
        size_t row = count/n, col = count%n;
        for (i_count = i = 0; i < n; i++)
            if (i != row)                   /* don't copy the current row*/
            {
                for (j_count = j = 0; j < n; j++)
                    if (j != col)           /* don't copy the current column */
                        mdata[i_count*M.col+j_count++] = A->data[i*A->col+j];
                i_count++;
            }
        /* transpose by swapping row and column */
        C.data[col*C.col+row] = pow(-1, (row&1) ^ (col&1)) * determinant(n-1, &M) / det;
    }
    memcpy(A->data, C.data, sizeof(double) * C.row * C.col);
	free(C.data);
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

struct matrix *find_node(struct matrix *head, char value) {

	while(head != NULL && head->value != value)
		head = head->next;
		
	return head;
}

void remove_spaces(char *str)
{ 
    int count = 0;
  
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
                                    
    str[count] = '\0';
}

void free_all(struct matrix *head)
{
	struct matrix *tmp;

    while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp->data);
       free(tmp);
    }
}

void halt(struct matrix *head, const char *error)
{
	free_all(head);
	printf("matrixlab syntax error: %s\n", error);
	exit(1);
}