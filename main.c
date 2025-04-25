#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
 

// -fopenmp

// Função para preencher a matriz com valores aleatórios
void preencher_matriz(int **matriz, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matriz[i][j] = rand() % 100; // Valores entre 0 e 99
        }
    }
}

// Função para multiplicar duas matrizes com paralelismo
void multiplicar_matrizes(int **A, int **B, int **C, int N) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Função para imprimir a matriz
void imprimir_matriz(int **matriz, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(NULL)); // Semente aleatória

    int N;
    printf("Digite o tamanho da matriz (N): ");
    scanf("%d", &N);

    // Alocação dinâmica correta de matrizes NxN
    int **A = (int **)malloc(N * sizeof(int *));
    int **B = (int **)malloc(N * sizeof(int *));
    int **C = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++) {
        A[i] = (int *)malloc(N * sizeof(int));
        B[i] = (int *)malloc(N * sizeof(int));
        C[i] = (int *)malloc(N * sizeof(int));
    }

    // Preencher as matrizes A e B
    preencher_matriz(A, N);
    preencher_matriz(B, N);

    // Medir tempo de execução
    double inicio = omp_get_wtime();
    multiplicar_matrizes(A, B, C, N);
    double fim = omp_get_wtime();

    printf("Tempo de execução: %f segundos\n", fim - inicio);

    // Exibir resultado (comentar se N for muito grande)
    if (N <= 10) {
        printf("Matriz C (Resultado do produto):\n");
        imprimir_matriz(C, N);
    }

    // Liberação de memória
    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}
