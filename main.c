/* Matrixlab 0.4
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

static struct option long_options[] = {
		/* Options without arguments */
		{"help",        no_argument,       NULL, 'h'},
		{"version",     no_argument,       NULL, 'V'},
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
    int arg_dim = DEFAULT_DIMENSION;
    int val;
    
    /* Read the parameters */
    while ((val = getopt_long (argc, argv, "VasArehlm:", long_options, NULL)) != -1) {
        switch (val) {
        case 'v':
        case 'V':
            printf ("Matrixlab %s \n"
                "Written by gioretikto \n\n"
                "This is free software; see the source for copying conditions. There is NO\n"
                "warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n",VERSION
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
        file = fopen(argv[1], "r");
        if (file == NULL) {
            fprintf(stderr, "Could not open input file %s: %s\n",
            argv[1], strerror(errno));
            return 1;
        }
    }

    if (argc > 2) {
        arg_dim = atoi(argv[2]);
        if ( arg_dim == 0) {
            fprintf(stderr, "Wrong dimension %s\n", argv[2]);
            fclose(file);
            return 1;
        }
    }
    read_file(arg_dim * arg_dim, file);
}