#include "functions.h"
#include <ctype.h>
#include <string.h>
#define MAXNOP 20 /*Max number of operations allowed */
#define MAXNMATR 40 /*Max number of matrices */
#define MAXLINE 500 /*Max lenght of a line */

void read_file(int maxc, FILE *fp)
{
	struct m matrix[MAXNMATR];
    struct operator op;

    size_t ncol, nrow;		    /* No of columns of a matrix */
    int off = 0;
    int i;
    int n;
    double *d;
    char buf[MAXLINE]; 			/* to store each lines of file */
    char *p = buf;
    
    ncol = nrow = 0;
    op.id = 0;
    op.nop = 0;
        
    for (i=0; i < MAXNOP; i++)
            op.symbol[i] = '?';    
   
    /*Read file line by line */
    while (fgets (buf, MAXLINE, fp)){
        
        if (strcmp(buf, "^-1\n") == 0){
                op.symbol[op.nop++] = 'i'; 	/* matrix inverse operation */
                continue;
        }
        
        if (strcmp(buf, "^T\n") == 0 || strcmp(buf, "^t\n") == 0){
                op.symbol[op.nop++] = 't'; 	/* matrix inverse operation */
                continue;
        }
            
        if (strcmp(buf, "det\n") == 0){
                op.symbol[op.nop++] = 'd'; 	/* determinant operation */
                continue;
        }
        
        if (nrow == 0){
            /* allocate/validate max no. of matrix */
            d = matrix[op.id].data = malloc(sizeof(double) * maxc);
        }
        
        /*check if line contains operator */
        if ( (!isdigit(*buf) && buf[1] =='\n'))
        {      
            op.symbol[op.nop++] = *buf;
            matrix[op.id].col = ncol;
            matrix[op.id].row = nrow;
            nrow = ncol = 0;
            op.id++;
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
    matrix[op.id].col = ncol;
    matrix[op.id].row = nrow;
    
    if (op.nop == 0) {
        fprintf(stderr, "Nothing to do\n");
        exit(1);
    }
    
    print_result(matrix, &op);
}