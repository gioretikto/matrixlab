/* Matrixlab
 *
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>
#include "functions.h"
#define DEFAULT_FILE stdin
#define DEFAULT_DIMENSION 100

static struct option long_options[] = {
		/* Options without arguments */
		{"help",        no_argument,       NULL, 'h'},
		{"version",     no_argument,       NULL, 'V'},
		{"random",      no_argument,       NULL, 'r'},
		{"endding",     no_argument,       NULL, 'e'},
		{"another",     no_argument,       NULL, 'a'},
		{"show",        no_argument,       NULL, 's'},
		{"another_any", no_argument,       NULL, 'A'},
		{NULL, 0, NULL, 0}
	};

static void
print_help (void)
{
	printf ("Matrixlab %s\n"
		"Usage: matrixlab path_to_file dimension\n\n"
		"  -h,  --help                   Print this help\n"
		"  -V,  --version                Print version and exit\n"
		"Report bugs to https://github.com/gioretikto/matrixlab\n", VERSION);
}

int main(int argc, char *argv[])
{
    
    FILE *file = DEFAULT_FILE;
    int maxc = DEFAULT_DIMENSION;
    int val;
    
    /* Read the parameters */
	while ((val = getopt_long (argc, argv, "VasArehlm:", long_options, NULL)) != -1) {
		switch (val) {
		case 'v':
		case 'V':
			printf ("Matrixlab 0.4 \n"
				"Written by gioretikto \n\n"
				"Copyright (C) 2003 Free Software Foundation, Inc.\n"
				"This is free software; see the source for copying conditions. There is NO\n"
				"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
				);
			exit(0);
			break;
		case 'h':
		case '?':
		default:
			print_help();
			exit(0);
			break;
		}
	}
	
	if (argc == 1) {
			print_help();
	    	return 1;
    }

    if (argc > 1) {
		file = fopen(argv[1], "rb");
		if (file == NULL) {
	    	fprintf(stderr, "Could not open input file %s: %s\n",
		    argv[1], strerror(errno));
	    	return 1;
		}
    }

    if (argc > 2) {
		int tmp;
		tmp = atoi(argv[2]) * atoi(argv[2]);
		if (tmp == 0) {
	   		fprintf(stderr, "Wrong dimension %s\n", argv[2]);
	    	fclose(file);
	    	return 1;
		}
		maxc = tmp;
    }

    read_file(maxc, file);
}