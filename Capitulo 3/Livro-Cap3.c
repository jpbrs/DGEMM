
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>

void dgemm(size_t n, double* A, double* B, double* C){
    for(size_t i = 0; i < n; i+=4){
        for(size_t j = 0; j < n; ++j){
            __m256d c0 = _mm256_setzero_pd(); /* c0 = C[i][j] */
            for(size_t k = 0; k < n; k++){
                c0 = _mm256_add_pd(c0, 
                /* c0 += A[i][k]*B[k][j] */ _mm256_mul_pd(_mm256_load_pd(A+i+k*n),
                _mm256_broadcast_sd(B+k+j*n)));
            }
            _mm256_storeu_pd(C+i+j*n, c0); /* C[i][j] = c0 */ // Lembrando que eh storeu pq a memoria nao ta alinhada
        }
    }
}

double* vetor(int n){
    double* temp;
    temp = (double*) malloc(n*sizeof(__m256d));
    // temp = (double*) aligned_alloc(n, n*sizeof(double));
    return temp;
}

int main(int argc, char *argv[]) // Passar como argumento um numero tipo 1000 para o algoritmo ir calculando o DGEMM de 10 em 10 até 1000
{
    char *argumento = argv[1];
    int n = atoi(argumento);
    char *compilacao = "O2";
    char *processador = "2.7 GHz Intel Core i5 Dual-Core";

    FILE *out_file = fopen("Resultados-Livro-Capitulo3-O2.csv", "w");
    fprintf(out_file, "N,CPU,Compilation Parameter,t(s)\n");

    for (int dim = 1; dim <=n; dim+=1 ){
        int len = dim*dim;
        double * a = vetor(len); // Criando Matriz/Vetor A com Zeros
        double * b = vetor(len); // Criando Matriz/Vetor B
        double * c = vetor(len);  // Por que double c[len] != double c[4]
        for (int i=0; i<len; i++){ // Setando os elementos das matrizes matrizes
            a[i] = i; // Matriz A = 1,2,3,...,N*N
            b[i] = -1*i; // Matriz B = -1,-2,-3,...,-N*N
        }

        clock_t start = clock();
        dgemm(dim, a, b, c);
        clock_t end = clock();
        double cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC; 
        fprintf(out_file, "%d,%s,%s,%f\n", dim, processador, compilacao, cpu_time_used);

        free(a);
        free(b);
        free(c);

    }

    fclose(out_file);
    return 0;
}
