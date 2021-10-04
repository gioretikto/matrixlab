<h1>Matrixlab v. 2.1</h1>

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

This is a GNU/Linux utility for manipulating and performing matrix operations. The matrix file containing the input data can be formatted in two ways:

<ol>

<li>
<p>by listing matrices seaparated by operators:</p>

<pre>
2 1 4
0 1 1
*
6 3 -1 0
1 1 0 4
-2 5 0 2
</pre>

<p>Execute with the following command:</p>

<pre>./matrixlab matrix matrmax_dim</pre>

<ul>
	<li><p>where matrix is the file containing the matrices</p></li>
	<li><p>matrmax_dim is the dimension of the largest matrix (3 in the example above)</p></li>
</ul>

<p>in the example above run: ./matrixlab matrix 3</p>

</li>


In addition to multiplications, additions, and subtractions, matrixlab can also perform: 

Determinant Calculation
--------------------------------
To calculate the determinant format the input file thus:

<pre>
4 -3 0
2 -1 2
1 5 7
det
</pre>

Transpositions
-------------------

<pre>
1 -2 4 
3 0 -5 
t
</pre>

Inverse of a matrix:
---------------------

<pre>
4 -3 0
2 -1 2
1 5 7
inv
</pre>

<h3>Some other complex calculation matrixlab can perform</h3>

<p>Imagine you want to solve the following system of linear equations:</p>

<p>Execture with command: ./matrixlab matrix 3</p>

<h3>Contacts</h3>

giovannirestadev@gmail.com
