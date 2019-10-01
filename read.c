#include "functions.h"
#include <ctype.h>
#include <string.h>
#define MAXNOP 20 /*Max number of operations allowed */
#define MAXNMATR 40 /*Max number of matrices */
#define MAXLINE 500 /*Max lenght of a line */

void read_file(int dim, FILE *fp)
{
    struct m matrix[MAXNMATR];
    struct operator op;
    size_t ncol, nrow;          /* No of columns, rows of a matrix */
    int off = 0;
    int check = 0;
    int max_id;
    double *d = NULL;
    int i, n;
    char line[MAXLINE];		/* to store each lines of file */
    char *buf;
    char tmpc;
    unsigned char map [MAXNMATR];

    ncol = nrow = 0;
    op.id = -1;
    op.nop = 0;
        
    for (i=0; i < MAXNOP; i++)
        op.symbol[i] = '?';
        
    i = 0;
   
    /*Read file line by line */
    while (fgets (buf = line, MAXLINE, fp)){
    
        if (strcmp(buf, "\n") == 0 || *buf == '\0'){
                continue;
        }
        
        while (isblank(*buf) && (*buf != '\0'))
        	buf++;
        
        if (strncmp(buf, "det", 3) == 0){
                op.symbol[op.nop++] = 'd';  /* determinant operation */
                continue;
        }
        
        if (strncmp(buf, "^-1", 3) == 0) {
                op.symbol[op.nop++] = 'i';  /* matrix inverse operation */
                continue;
        }
        
        if (strncmp(buf, "^T", 2) == 0 || strncmp(buf, "^t", 2) == 0) {
                op.symbol[op.nop++] = 't';  /* matrix transpose operation */
                continue;
        }
      
        /* check if line contains operator */
        if ( (*buf == '*' || *buf == '+' || *buf == '-') && buf[1] == '\n')
        {
            op.symbol[op.nop++] = *buf;
            matrix[op.id].col = ncol;
            matrix[op.id].row = nrow;
            nrow = ncol = 0;
            check = 0;
            continue;
        }
        
        if(isdigit(*buf) || ((*buf == '+' || *buf == '-') && isdigit(buf[1]) && (check < dim)) ) {
        
            if(check == 0){
                op.id++;
                d = matrix[op.id].data = malloc(sizeof(double) * dim);
            }
            
            /* read numbers in a line into d */
            while (sscanf (buf + off, "%lf%n", d, &n) == 1) {
                    if(check != dim - 1)
                        d++;
                    if (nrow == 0)
                       ncol++;
                    off += n;
                    check++;
            }
            nrow++;
	        off = 0;
        }         

        matrix[op.id].col = ncol;
    	matrix[op.id].row = nrow;
        
        if (isupper(*buf)) {
        	  tmpc = *buf;
        	  buf++;
        
        while(isblank(*buf))
        		buf++;
        		
        if ( *buf == '=') { /* check matrix initialization like A =\n 1 0 0 \n 2 0 ... */
                map[op.id + 1] = tmpc - 'A';
                nrow = ncol = 0;
                check = 0;
                continue;
        }
        
        if(*buf != '=' && (op.id >= 0) ) {
        	putchar(tmpc);
            	max_id = op.id;
        	op.id = 0;        	

		    while(*buf != '\0'){
			int index;
		    	index = mapping(max_id, map, *buf);
		    	if(isupper(*buf) && index != op.id){
		    		struct m tmp;
					tmp.row = matrix[op.id].row;
					tmp.col = matrix[op.id].col;
					tmp.data = malloc(sizeof(double) * tmp.row * tmp.col);
					memcpy(tmp.data, matrix[op.id].data, sizeof(double) * tmp.row * tmp.col);
					memcpy(matrix[op.id].data, matrix[index].data, sizeof(double) * matrix[index].row * matrix[index].col);
					memcpy(matrix[index].data, tmp.data, sizeof(double) * tmp.row * tmp.col);
					tmpc = map[op.id];
					map[op.id] = tmpc - 'A';
					map[index] = tmpc;
					free(tmp.data);
				}
				
				printf("%c", *buf);
			
		        if(!isupper(*buf) && !isblank(*buf)){
		            op.symbol[op.nop++] = *buf;
		            op.id++;
		        }

		        buf++;
		    }
		    op.id = max_id;
		    printf("=\n");
        }

	} /*end of if (isupper(buf[i]) */

    }   /* end of while fgets cycle */

    fclose(fp);
    
    if (op.nop == 0) {
        fprintf(stderr, "Nothing to do\n");
        exit(1);
    }
 
    display_data(matrix, &op);
}