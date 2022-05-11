#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

double* vetor(int n){
    double* temp;
    temp = (double*) malloc(n*sizeof(double));
    return temp;
}

int main(int argc, char *argv[]) // Passar como argumento um numero tipo 1000 para o algoritmo ir calculando o DGEMM de 10 em 10 até 1000
{
    char *argumento = argv[1];
    int n = atoi(argumento);
    char *compilacao = "O0";
    char *processador = "2.7 GHz Intel Core i5 Dual-Core";

    FILE *out_file = fopen("results-O0-i5.csv", "w");
    fprintf(out_file, "N,CPU,Compilation Parameter,t(s)\n");

    for (int dim = 10; dim <=n; dim+=10 ){
        int len = dim*dim;
        clock_t start, end;
        double cpu_time_used;

        double * a = vetor(len); // Criando Matriz/Vetor A com Zeros
        double * b = vetor(len); // Criando Matriz/Vetor B
        double * c = vetor(len);  // Por que double c[len] != double c[4]
        for (int i=0; i<len; i++){ // Setando os elementos das matrizes matrizes
            a[i] = i; // Matriz A = 1,2,3,...,N*N
            b[i] = -1*i; // Matriz B = -1,-2,-3,...,-N*N
        }

        start = clock();
        dgemm(dim, a, b, c);
        end = clock();
        cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
        fprintf(out_file, "%d,%s,%s,%f\n", dim, processador, compilacao, cpu_time_used);
    }

    fclose(out_file);
    return 0;
}
