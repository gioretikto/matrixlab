<h1>Matrixlab v. 1.0</h1>

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

<h2>USAGE</h2>
------------------------------
This is a GNU/Linux utility for manipulating and performing matrix operations.
The matrix file containing the input data is thus formatted:

<pre>
-1 2 3
0 1 3
0 4 5
*
4 0
1 2
-2 3

Execute with the following command:
	./matrixlab matrix matrmax_dim

<ul>
	<li><p>where matrix is the file containing the matrices</p></li>
	<li><p>matrmax_dim is the dimension of the largest matrix (3 in the example above)</p></li>
</ul>

in the example above run: ./matrixlab matrix 3

or you can initialize matrices separately by using capital letters and input the expression at the end thus:

<pre>
A =
1 1
2 1

B=
2 1
1 1

C=
1 0
0 1

C*B*A
</pre>
	
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

Some other complex calculation matrixlab can perform
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

Execture command: ./matrixlab matrix 3

<h3>Coming in the next update</h3>

We're trying to implement a new functionality in order to perform also symbolic operation, like:

evaluation of algebraic expressions

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

Contacts

You can reach me on the freenode IRC channel #cansi
