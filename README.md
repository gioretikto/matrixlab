# Matrixlab v. 0.4

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

USAGE
------------------------------
This is a GNU/Linux utility for manipulating and performing matrix operations.
The matrix file containing the input data is thus formatted:

<pre>
1 2 3
-1 2 3
0 1 3
0 4 5
*
4 0
1 2
-2 3
</pre>

Execute with the following command:
	./matrixlab matrix matrmax_dim

-where matrix is the file containing the matrices
-matrmax_dim is the dimension of the largest matrix (3 in the example above)

in the example above run:

	./matrixlab matrix 3
	
In addition to multiplications, additions, and subtractions, matrixlab can also perform: 

Determinant Calculation
--------------------------------
To calculate the determinant format the input file thus:

<pre>
det
4 -3 0
2 -1 2
1 5 7
</pre>

Transpositions
-------------------
<pre>
1 -2 4 
3 0 -5 
^T
</pre>

Inverse of a matrix:
---------------------

<pre>
4 -3 0
2 -1 2
1 5 7
^-1
</pre>


Some other complex calculation matrixlab can do
-------------------------------------------------

<pre>
2
*
5 6 7
8 9 8
1 2 3
det
1 0 0
0 1 0
0 0 1
+
1 1 1
1 1 1
1 1 1
</pre>

<p>Execture command: ./matrixlab matrix 3</p>


<h2>Coming in the next update</h2>

For the next version I'd like the program to perform also symbolic operation, like:

<ul>
<li><p>Inizialization of matrices:</p>
<pre>
A=
1 1
2 1

B=
5 6
7 8

A*B
</pre>
</li>

<li><p>evaluation of algebraic expressions</p>

<pre>
cos x sin x
cos x 5
*
1 0
0 1
=
cos x sin x
cos x 5
</pre>
</li>
</ul>

<h3>Contacts</h3>

You can reach me on the freenode IRC channel #cansi
