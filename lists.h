#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct matrix
{
	long double *data;
	struct matrix *next;
	char op;
	size_t row;
	size_t col;
};
