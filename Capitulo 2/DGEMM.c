#include <stdio.h>

/* Programa do Livro */
void dgemm(int n, double* A, double* B, double* C){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            double cij = C[i+j*n]; /* cij = C[i][j] */
            for (int k = 0; k < n; k++){
                cij += A[i+k*n] * B[k+j*n]; /* cij += A[i][k]*B[k][j] */
            }
            C[i+j*n] = cij; /* C[i][j] = cij */
        }
    }
}

int main(void)
{
    double a[] = { 1.0, 2.0,
                    2.0, 1.0}; // 2x2

    double b[] = { 1.0, 1.0,
                     1.0, 1.0}; // 2x2

    double c[] = { 0.00, 0.00,
                   0.00, 0.00 }; // 2x2

    /* Compute C = AB */

    dgemm(2, a, b, c);

    printf("[[ %g, %g ]\n",  c[0], c[1]);
    printf(" [ %g, %g ]]\n", c[2], c[3]);

    return 0;
}
