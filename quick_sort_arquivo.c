#include <stdio.h>
#include <stdlib.h>

//Iniciar as funções antes das implementações
void ordena_quick_sort(float *dados, int inicio, int fim);
int particiona(float *dados, int inicio, int fim);

int main() {

    //Le o arquivo.
    //FILE = Tipo de arquivo
    // *arquivo = Ponteiro de arquivo
    // fopen = função que lê o arquivo e define as permissões
    // "r" = read = ler = apenas podemos ler o arquivo
    FILE *arquivo = fopen("kz_limpo_numero_3.csv", "r");

    //Verifica se o arquivo não é NULO, por falta de linhas ou por não ter encontrado e etc.
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    int capacidade = 500000; // Capacidade inicial para 500.000 números
    float *dados = malloc(capacidade * sizeof(float));  // Aloca um array dinâmico

    //Verifica se a memória foi alocada na memoria de forma correta.
    if (dados == NULL) {
        perror("Erro ao alocar memória");
        //fecha o arquivo.
        fclose(arquivo);
        return EXIT_FAILURE;
    }

    //contador de linhas
    int linhas = 0;
    //vetor para guardar a linha atual.
    char linha[50]; // Buffer para cada linha

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Expande o array se atingir a capacidade
        if (linhas >= capacidade) {
            capacidade *= 2;
            dados = realloc(dados, capacidade * sizeof(float));
            if (dados == NULL) {
                perror("Erro ao expandir a memória");
                fclose(arquivo);
                return EXIT_FAILURE;
            }
        }
        
        // Converte a linha para float e armazena
        dados[linhas] = strtof(linha, NULL);
        linhas++;
    }

    //Fecha o arquivo para evitar problemas de memoria.
    fclose(arquivo);

    // Ordena os dados usando Quick Sort
    ordena_quick_sort(dados, 0, linhas - 1);

    printf("Total de linhas lidas do arquivo CSV: %d\n", linhas);
    
    // Exibe os primeiros 10 dados para verificação
    for (int i = 0; i < 2000 && i < linhas; i++) {
        printf("%.2f\n", dados[i]);
    }

    free(dados);  // Libera a memória alocada

    return EXIT_SUCCESS;
}

// Função para dividir o array e retornar o índice do pivô
int particiona(float *dados, int inicio, int fim) {
    float pivo = dados[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (dados[j] <= pivo) {
            i++;
            float temp = dados[i];
            dados[i] = dados[j];
            dados[j] = temp;
        }
    }

    float temp = dados[i + 1];
    dados[i + 1] = dados[fim];
    dados[fim] = temp;

    return i + 1;
}

// Implementação do Quick Sort
void ordena_quick_sort(float *dados, int inicio, int fim) {
    if (inicio < fim) {
        int indice_pivo = particiona(dados, inicio, fim); // Índice do pivô
        ordena_quick_sort(dados, inicio, indice_pivo - 1);  // Ordena elementos à esquerda do pivô
        ordena_quick_sort(dados, indice_pivo + 1, fim);     // Ordena elementos à direita do pivô
    }
}
