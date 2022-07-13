#include <x86intrin.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define UNROLL (4)
#define BLOCKSIZE 32

void do_block (int n, int si, int sj, int sk, double *A, double *B, double *C){
    for (int i=si; i < si+BLOCKSIZE; i+=UNROLL*8){
        for (int j=sj; j<sj+BLOCKSIZE; j++){
            __m256d c[UNROLL];
            // printf("\nPonto 1\n");
            for (int r=0; r<UNROLL; r++){
                c[r] = _mm256_loadu_pd(C+i+r*8+j*n);
            }
            // printf("\nPonto 2\n");
            for (int k=sk; k< sk+BLOCKSIZE; k++){
                __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B+j*n+k));
                // printf("\nPonto 2.1\n");
                for (int r=0; r<UNROLL; r++){
                    c[r] = _mm256_fmadd_pd(_mm256_loadu_pd(A+n*k+r*8+i) , bb, c[r]);
                } 
                // printf("\nPonto 2.2\n");
            }
            // printf("\nPonto 3\n");
            for (int r=0; r<UNROLL; r++){
                _mm256_storeu_pd(C+i+r*8+j*n, c[r]);
            }
        }
    }
}

double dgemm (int n, double* A, double *B, double* C){
    clock_t start = clock();
    for (int sj = 0; sj < n; sj+=BLOCKSIZE){
        for (int si = 0; si < n; si += BLOCKSIZE){
            for (int sk = 0; sk <n ; sk += BLOCKSIZE){
                do_block(n, si, sj, sk, A, B, C);
            }
        }
    }
    clock_t end = clock();

    // printf("\nMatriz C\n");
    // for (int i=0; i<n; i++){
    //     for (int j=0; j<n; j++){
    //         printf("%.2f, ",C[i+j*n]);
    //     }
    //     printf("\n");
    // }

    // printf("%.2f, ",C[n-1+(n-1)*n]);

    double cpu_time_used = ((double) (end-start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

double* vetor(int n){
    double* temp;
    temp = (double*) malloc(n*sizeof(__m256d));
    // temp = (double*) aligned_alloc(n, n*sizeof(__m256d));
    return temp;
}

int main(int argc, char *argv[]) // Passar como argumento um numero tipo 1000 para o algoritmo ir calculando o DGEMM de 10 em 10 até 1000
{
    char *argumento = argv[1];
    int n = atoi(argumento);
    char *compilacao = "O1";
    char *processador = "2.7 GHz Intel Core i5 Dual-Core";

    FILE *out_file = fopen("results-O1-i5-Cap5-Block32.csv", "w");
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

        // printf("\n Multiplicação de Matrizes %dx%d \n", dim,dim);

        // printf("\nMatriz A\n");
        // for (int i=0; i<dim; i++){
        //     for (int j=0; j<dim; j++){
        //         printf("%.2f, ",a[i+j*dim]);
        //     }
        //     printf("\n");
        // }

        // printf("\nMatriz B\n");
        // for (int i=0; i<dim; i++){
        //     for (int j=0; j<dim; j++){
        //         printf("%.2f, ",b[i+j*dim]);
        //     }
        //     printf("\n");
        // }

        cpu_time_used = dgemm(dim, a, b, c);
        fprintf(out_file, "%d,%s,%s,%f\n", dim, processador, compilacao, cpu_time_used);

        free(a);
        free(b);
        free(c);

        // printf("--------------------------------------------------------------\n");
    }

    fclose(out_file);
    return 0;
}