#include <math.h>
#include "functions.h"

/*Calculate the inverse of a matrix */

void inverse(size_t n, struct m *A)
{
    double det;
    if ((det = determinant(n, A)) == 0) {
        printf("The matrix is singular\n");
        exit(1);
    }

    size_t i, j, i_count, j_count, count = 0;

    struct m C;                 /*The Adjoint matrix */
    C.data = malloc(sizeof(double) * n * n);

    C.row = n;
    C.col = n;
    double Rdata[(n - 1) * (n - 1)];    // remaining data values
    struct m R = { n - 1, n - 1, Rdata };   // matrix structure for them
    for (count = 0; count < n * n; count++) // Create n*n Matrix of Minors
    {
        int row = count / n, col = count % n;
        for (i_count = i = 0; i < n; i++)
            if (i != row)       // don't copy the current row
            {
                for (j_count = j = 0; j < n; j++)
                    if (j != col)   // don't copy the current column
                        Rdata[i_count * R.col + j_count++] =
                            A->data[i * A->col + j];
                i_count++;
            }
        // transpose by swapping row and column
        C.data[col * C.col + row] =
            pow(-1, (row & 1) ^ (col & 1)) * determinant(n - 1, &R) / det;
    }
    free(A->data);
    *A = C;
}
