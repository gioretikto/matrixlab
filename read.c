#include "functions.h"
#include <ctype.h>
#include <string.h>
#define MAXNOP 20 /*Max number of operations allowed */
#define MAXNMATR 40 /*Max number of matrices */
#define MAXLINE 500 /*Max lenght of a line */

void read_file(int maxc, FILE *fp)
{
	struct m matrix[MAXNMATR];
    int id;						/* id of a matrix */
    size_t ncol, nrow;		    /* No of columns of a matrix */
    int nop = 0;			    /* No of operators */
    int off = 0;
    int i;
    int n;
    double *d;
    char buf[MAXLINE]; 			/* to store each lines of file */
    char *p = buf;
    char op[MAXNOP];
    
    id = 0;
    ncol = nrow = 0;    
    
    for (i=0; i < MAXNOP; i++)
            op[i]='?';    
   
    /*Read file line by line */
    while (fgets (buf, MAXLINE, fp)){
        
        if (strcmp(buf, "^-1\n") == 0){
                op[nop++] = 'i'; /* matrix inverse operation */
                continue;
        }
        
        if (strcmp(buf, "^T\n") == 0 || strcmp(buf, "^t\n") == 0){
                op[nop++] = 't'; /* matrix inverse operation */
                continue;
        }
            
        if (strcmp(buf, "det\n") == 0){
                op[nop++] = 'd'; 	/* determinant operation */
                continue;
        }
        
        if (nrow == 0){
            /* allocate/validate max no. of matrix */
            d = matrix[id].data = malloc(sizeof(double) * maxc);
        }
        
        /*check if line contains operator */
        if ( (!isdigit(*buf) && buf[1] =='\n'))
        {      
            op[nop++] = *buf;
            matrix[id].col = ncol;
            matrix[id].row = nrow;
            nrow = ncol = 0;
            id++;
            continue;
        }
        
        /* read integers in a line into d */
        while (sscanf (p + off, "%lf%n", d, &n) == 1) {
            d++;
            if (nrow == 0)
               ncol++;
            off += n;
        }
            
        nrow++;
        off = 0;
    }				/* end of while fgets cycle */

	fclose(fp);
       
    /* Assign last matrix No of columns and rows */
    matrix[id].col = ncol;
    matrix[id].row = nrow;
    
    if (nop == 0) {
        fprintf(stderr, "Nothing to do\n");
        exit(1);
    }        
    
    /* Printing the matrices and operations */
    for(i=0; i <= id; i++){
                     
        if(op[i] == 'd'){
            printf("det\n");
            print_matrix(&matrix[i]);
            continue;
        }
        
        if (op[i] == '*' || op[i] == '-' || op[i] =='+')
        {
            print_matrix(&matrix[i]);
            if(op[i - 1] == 'i' || op[i - 1] == 'T' || op[i - 1] == 't')
                continue;
            else
                printf("%c\n", op[i]);
        }
        
         if (op[i] == 't' || op[i] == 'T'){            
             print_matrix(&matrix[i]);
             printf("^T\n");
             if(op[i+1] != '?')
                printf("%c\n",op[i+1]);
             continue;
        }
        
         if (op[i] == 'i'){
            print_matrix(&matrix[i]);
            printf("^-1\n"); 	/* matrix inverse operation */
            if(op[i+1] != '?')
                printf("%c\n",op[i+1]);
            continue;
        }
        
         if(op[i] == '?'){
             print_matrix(&matrix[i]);
        }        
    }
    
    calculate(matrix, nop, id, op);
}