#include <stdio.h>
#include <stdlib.h>

// prototipo das funçoes 
void ordena_quick_sort(int *dados, int inicio, int fim);
int particiona(int *dados, int inicio, int fim);
void trocar(int *a, int *b);
void imprimirArray(int *array, int tamanho);

int main() {
    int array[] = {10, 7, 8, 9, 1, 5};
    int tamanho = sizeof(array) / sizeof(array[0]);

    printf("Array original: ");
    imprimirArray(array, tamanho);

    // funçao para ondenar o array
    ordena_quick_sort(array, 0, tamanho - 1);

    printf("Array ordenado: ");
    imprimirArray(array, tamanho);

    return 0;
}

// divide o array e retorna o indece do pivõ
int particiona(int *dados, int inicio, int fim) {
    int pivo = dados[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (dados[j] <= pivo) {
            i++;
            trocar(&dados[i], &dados[j]);
        }
    }

    trocar(&dados[i + 1], &dados[fim]);
    return i + 1;
}

// execuçao do Quick Sort
void ordena_quick_sort(int *dados, int inicio, int fim) {
    if (inicio < fim) {
        int indice_pivo = particiona(dados, inicio, fim);
        ordena_quick_sort(dados, inicio, indice_pivo - 1);
        ordena_quick_sort(dados, indice_pivo + 1, fim);
    }
}

// funçao para trocar dois elementos
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// imprime o array 
void imprimirArray(int *array, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
