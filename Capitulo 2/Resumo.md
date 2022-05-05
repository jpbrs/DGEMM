# Resumo do Going Faster Capitulo 2

Nessa parte da matéria, o autor cria uma função que ao invés de receber uma matrix NxN como parâmetro, recebe apenas um vetor de tamanho N^2. Dessa maneira, ele diz que utilizando a aritmética para acessar os elementos (como por exemplo : double cij = C[i+j*n]; /* cij = C[i][j] */) o código ganha performance.

# Adicionais que pretendo colocar

1. Comparar com um código de multiplicação de matrizes normal que realize tudo em um vetor NxN
2. Inverter a ordem dos "for" para identificar se existe algum ganho de performance
3. Ver o comportamento de ambas em um gráfico t(s) x N e comparar o desempenho de ambas