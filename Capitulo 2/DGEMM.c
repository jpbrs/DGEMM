#include <stdio.h>
#include <stdlib.h>

/////////////* Programa do Livro *//////////////////////

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
//***************************************************//
double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

double* vetor(int n){
    double* temp;
    temp = (double*) malloc(n*sizeof(double));
    return temp;
}

int main(int argc, char *argv[])
{
    char *argumento = argv[1];
    int n = atoi(argumento);
    int len = n*n;

    double A[] = { 1.0, 2.0,
                    3.0, 4.0}; // 2x2
    double B[] = { 5.0, 6.0,
                     7.0, 8.0}; // 2x2
    double C[] = { 0.00, 0.00,
                   0.00, 0.00 }; // 2x2

    /* Compute C = AB */
    dgemm(2, A, B, C);

    printf("\n Feito A x B \n");
    printf("\nMatriz A - Linha \n");
    printf("[ %g, %g ]\n",  A[0], A[2]);
    printf("[ %g, %g ]\n", A[1], A[3]);
    printf("\nMatriz B - Coluna \n");
    printf("[ %g, %g ]\n",  B[0], B[2]);
    printf("[ %g, %g ]\n", B[1], B[3]);
    printf("\n--- Matriz Resultado ---\n");
    printf("[ %g, %g ]\n",  C[0], C[2]);
    printf("[ %g, %g ]\n", C[1], C[3]);

    double * a = vetor(len);
    for (int i = 0; i<len; i++){
        a[i] = randfrom(1.0, 10.0);
    }
    double * b = vetor(len);
    int w = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            if (i==j){
                b[w] = 1;
            }
            else{
                b[w] = 0;
            }
            w++;
        }
    }
    // for (int i = 0; i<len; i++){
    //     b[i] = randfrom(1.0, 10.0);
    // }
    double * c = vetor(len);  // Por que double c[len] != double c[4]

    dgemm(2, a, b, c);

    printf("\n Feito a x b \n");
    printf("\nMatriz a - Linha \n");
    printf("[ %g, %g ]\n",  a[0], a[2]);
    printf("[ %g, %g ]\n", a[1], a[3]);
    printf("\nMatriz b - Coluna \n");
    printf("[ %g, %g ]\n",  b[0], b[2]);
    printf("[ %g, %g ]\n", b[1], b[3]);
    printf("\n--- Matriz Resultado ---\n");
    printf("[ %g, %g ]\n",  c[0], c[2]);
    printf("[ %g, %g ]\n", c[1], c[3]);


    return 0;
}
