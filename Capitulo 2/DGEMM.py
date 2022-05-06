import time
import sys

m = sys.argv[1]
m = int(m)

with open("results-i5-py-line.csv","w+") as python_file:
    python_file.write("N,CPU,Compilation Parameter,t(s)\n")
    for n in range(10,m,10):
        A = [e for e in range(0, n*n)]
        B = [e * -1 for e in range(0, n*n)]
        C = [0 for e in range(0, n*n)]

        start_time = time.time()
        for i in xrange(n):
            for j in xrange(n):
                cij = C[i+j*n]
                for k in xrange(n):
                    cij += A[i+k*n] * B[k+j*n]
                C[i+j*n] = cij
        execution_time = time.time() - start_time
        python_file.write("{},{},{},{}\n".format(n,"2.7 GHz Intel Core i5 Dual-Core","Python",execution_time))
        # print(C[0][0],C[0][1])
        # print(C[1][0],C[1][1])
