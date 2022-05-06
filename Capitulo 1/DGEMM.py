import time
import sys

m = sys.argv[1]
m = int(m)

with open("results-i5-py-switched.csv","w+") as python_file:
    python_file.write("N,CPU,Compilation Parameter,t(s)\n")
    for n in range(10,m,10):
        A = []
        B = []
        C = []

        for elemento in range(0,n*n, n):
            A.append([e for e in range(elemento, elemento+n)])
            B.append([e * -1 for e in range(elemento, elemento+n)])
            C.append([0 for e in range(elemento, elemento+n)])

        # print(A[0][0],A[0][1])
        # print(A[1][0],A[1][1])

        # print(B[0][0],B[0][1])
        # print(B[1][0],B[1][1])

        start_time = time.time()
        for j in xrange(n):
            for i in xrange(n):
                for k in xrange(n):
                    C[i][j] += A[i][k] * B[k][j]
        execution_time = time.time() - start_time
        python_file.write("{},{},{},{}\n".format(n,"2.7 GHz Intel Core i5 Dual-Core","None",execution_time))
        # print(C[0][0],C[0][1])
        # print(C[1][0],C[1][1])
