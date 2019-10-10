#include "functions.h"
#include <ctype.h>
#include <string.h>

void read_file(int dim, FILE *fp)
{
	struct matrix *head = NULL;
	int check, n, off;
	check = off = 0;
    double data[dim];
	double *d = data;
    char line[MAXLINE];		/* to store each lines of file */
    char *buf = line;
	size_t ncol, nrow;
	ncol = nrow = 0;
	_Bool unary[3];
	unary[0] = unary[1] = unary[2] = 0;
	char value, tmpc;
	char operator[4] = {'\0'};
	double k;
	char *rest;
	int map[25] = {0};
	
	/* Read file line by line */
    while (fgets (buf = line, MAXLINE, fp)) {
    
    	if(*buf =='/')
    		halt(head, "you cannot divide matrices");
    
        if (strncmp(buf, "det", 3) == 0) {
                operator[0] = 'd';  /* determinant operation */
                unary[2] = 1;
                continue;
        }
        
        if (strncmp(buf, "^-1", 3) == 0) {
                operator[1] = 'i';  /* matrix inverse operation */
                unary[0] = 1;
                continue;
        }
        
        if (strncmp(buf, "^T", 2) == 0) {
                operator[3] = 't';  /* matrix transpose operation */
                unary[1] = 1;
                continue;
        }
        
        if (isupper(*buf)) {
        	  tmpc = *buf;
        	  buf++;
        
		    while(isblank(*buf))
		    		buf++;
		    		
		    if (*buf == '=') { /* check matrix initialization a row like: A =\n 1 0 0 \n 2 0 ... */
		    	    
		            if(check != 0) {
		            	add_item(&head, data, nrow, ncol, operator, value);
		            	d = data;
		            }
		            
   		            value = tmpc;
		            nrow = ncol = 0;
		            check = 0;
		            continue;
		    }
        }

 		/* check if line contains operator */
        if ((*buf == '*' || *buf == '+' || *buf == '-') && buf[1] == '\n')
        {
        	operator[2] = *buf;
	   		add_item(&head, data, nrow, ncol, operator, '\0');
            nrow = ncol = 0;
            check = 0;
			d = data;
			operator[0] = operator[1] = operator[2] = operator[3] = '\0';
            continue;
        }
        
        if(isdigit(*buf) || (*buf == '+' || *buf == '-')){
        	if(check < dim) {       
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
		}
	} /* end of while */

	fclose(fp);
	
	if (check != 0) { /* parse the expression */
	
		add_item(&head, data, nrow, ncol, operator, value);
		remove_spaces(buf);
		
		struct matrix *tmp = NULL;
		
		printf("%s = \n\n", buf);
		
		while(*buf != '\0') {
		
			if(islower(*buf))
				halt(head, "you cannot use lower case letters to represent matrices");
		
			if (isdigit(*buf) || ((*buf == '-' || *buf == '+') && isdigit(buf[1]))) {
			
				k = strtod(buf, &rest);
				
				buf = rest;
				
				while (!isupper(*buf)) {
					buf++;
					if (*buf == '+' || *buf == '-' || *buf == '*') {
						if(!isupper(buf[-1]) && !isdigit(buf[-1]))
							halt(head, "Double operator detected");
					}
				}
				
				if(map[*buf-'A'] > 0) {
					
					tmp = find_node(head, *buf);
					
					for (tmpc = 'A'; tmpc <= 'Z'; tmpc++)
						if ((find_node(head, tmpc)) == NULL)
							break;
					
					add_item(&head, tmp->data, tmp->row, tmp->col, operator, tmpc);
					tmp = head;
					map[tmpc-'A']++;
					if(isupper(buf[1]))
						tmp->op[2] = '*';
				}					
					
				else { 
					if((tmp = find_node(head, *buf)) == NULL) 
						halt(head, "matrix not found");
					scalar_product(k, tmp);
					map[*buf-'A']++;
					if(isupper(buf[1]))
						tmp->op[2] = '*';
				}
				buf++;			
		    }
			
			if (strncmp(buf, "det", 3) == 0) {
                unary[2] = 1;
                buf += 3;
                tmp = find_node(head, *buf);
                tmp->op[0] = 'd';
                buf++;
        	}
        	
        	if (strncmp(buf, "^T", 2) == 0) {
                unary[1] = 1;
				tmp->op[3] = 't';
				buf += 2;
        	}
        	
        	if (strncmp(buf, "^-1", 3) == 0) {
                unary[0] = 1;
                tmp->op[1] = 'i';
                buf += 3;
			}
			
			if (isupper(*buf)) {
				if(map[*buf-'A'] > 0) {
					tmp = find_node(head, *buf);
					
					for (tmpc = 'A'; tmpc <= 'Z'; tmpc++)
						if ((find_node(head, tmpc)) == NULL)
							break;					
					
					add_item(&head, tmp->data, tmp->row, tmp->col, operator, tmpc);
					tmp = head;
					map[tmpc-'A']++;
					if(isupper(buf[1]))
						tmp->op[2] = '*';
				}					
					
				else {
					if((tmp = find_node(head, *buf)) == NULL) 
						halt(head, "matrix not found");
					map[*buf-'A']++;
					if(isupper(buf[1]))
						tmp->op[2] = '*';
				}
				buf++;	
			}
			
			if (*buf == '+' || *buf == '-' || *buf == '*') {
				if(tmp != NULL && !isupper(buf[-1]) && !isdigit(buf[-1])) {
					halt(head, "double operator detected");
				}
				tmp->op[2] = *buf;
				buf++;
			}
		}
	}

	print_list(head);

	printf("=\n");
	
	if(unary[1] == 1)
		trans(head); /* Transpose */
	
	if(unary[0] == 1)
		inv(head);
	
	if(unary[2] == 1)
		det(head);

	multiplication(head);

	summation(head);

	print_list(head);
	
	free(head->data);
	
	free(head);	
}