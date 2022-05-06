#include<stdio.h>
#include<stdlib.h>


void dgemm (int n, double *A, double *B, double *C) { 

	for(int i =0; i < n; ++i) {
		for(int j=0; j<n; ++j) {
			double cij = C[i+j*n];
			for (int k = 0; k < n; k++) {
				cij += (A[i+k*n]) * (B[k+j*n]);
			C[i+j*n] = cij;
			}
		}
	}
	
	for(int i = 0; i < (n*n); i++) {
		printf("%2.0f\n",C[i]);
	}

}


int main () {

	int n = 3;
	
	double * c = (double *)malloc((n*n) * sizeof(double));
	double * b = (double *)malloc((n*n) * sizeof(double));
	double * a = (double *)malloc((n*n) * sizeof(double));
	

    	
    	for (int i = 0; i < (n*n); i++) {
        	c[i] = 0.0;
        }

    	for (int i = 0; i < (n*n); i++) {
        	b[i] = (double)i + 1;
        }

    	for (int i = 0; i < (n*n); i++) {
        	a[i] = (double)i + 1;
        }

	
	dgemm(n,a,b,c);
}











