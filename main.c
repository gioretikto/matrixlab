/* Freelab
 *
 * Authors:
 *      Giovanni Resta <giovanniresta87@gmail.com>
 *
 * Copyright (C) 2019 Giovanni Resta
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
#include <ctype.h>
#include <math.h>
#include "functions.h"

int main(int argc, char *argv[]){
    
    FILE *file = argc > 1 ? fopen(argv[1], "rb") : stdin;
   
    /*define max dimension of a matrix */
    int maxc = argc>2?atoi(argv[2])*atoi(argv[2]):100;
    
    read_file(maxc, file);       
 
    return 0;
}
