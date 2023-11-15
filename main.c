#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para gerar um arquivo de texto com números inteiros aleatórios
void gerar_arquivo_numeros(char *name_arquivo, int quant) {
    FILE *arquivo = fopen(name_arquivo, "w");
    if (arquivo == NULL) {
        printf("Error 500!\n");
        exit(1);
    }

    srand(time(NULL));
    for (int i = 0; i < quant; i++) {
        int num1 = rand() % 1000 + 1;
        fprintf(arquivo, "%d\n", num1);
    }

    fclose(arquivo);
}

// Função para realizar a busca linear em um arquivo de números
double busca_linear(int num1, char *name_arquivo) {
    FILE *arquivo = fopen(name_arquivo, "r");
    if (arquivo == NULL) {
        printf("Error 400!.\n");
        exit(1);
    }

    double start_time = (double)clock() / CLOCKS_PER_SEC; // Registra o tempo de início

    int encontrado = 0;
    int num;
    while (fscanf(arquivo, "%d", &num) != EOF) {
        if (num == num1) {
            encontrado = 1;
            break;
        }
    }

    double end_time = (double)clock() / CLOCKS_PER_SEC; // Registra o tempo de término

    fclose(arquivo);

    if (encontrado) {
        return end_time - start_time;
    } else {
        return -1.0;
    }
}

// Função para realizar a busca sentinela em um arquivo de números
double busca_sentinela(int num1, char *name_arquivo) {
    FILE *arquivo = fopen(name_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    double start_time = (double)clock() / CLOCKS_PER_SEC; // Registra o tempo de início

    int encontrado = 0;
    int num;
    while (fscanf(arquivo, "%d", &num) != EOF) {
        if (num == num1) {
            encontrado = 1;
            break;
        }
    }

    double end_time = (double)clock() / CLOCKS_PER_SEC; // Registra o tempo de término

    fclose(arquivo);

    if (encontrado) {
        return end_time - start_time;
    } else {
        return -1.0;
    }
}

// Função para realizar a busca binária em um arquivo de números
double busca_binaria(int num1, char *name_arquivo) {
    FILE *arquivo = fopen(name_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int *numeros = NULL;
    int tamanho = 0;

    int num;
    while (fscanf(arquivo, "%d", &num) != EOF) {
        tamanho++;
        numeros = (int *)realloc(numeros, tamanho * sizeof(int));
        numeros[tamanho - 1] = num;
    }

    fclose(arquivo);

    // Ordena a lista de números para a busca binária
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (numeros[i] > numeros[j]) {
                int temp = numeros[i];
                numeros[i] = numeros[j];
                numeros[j] = temp;
            }
        }
    }

    double start_time = (double)clock() / CLOCKS_PER_SEC; // Registra o tempo de início
    int encontrado = 0;
    int esquerda = 0;
    int direita = tamanho - 1;
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (numeros[meio] == num1) {
            encontrado = 1;
            break;
        }
        if (numeros[meio] < num1) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    double end_time = (double)clock() / CLOCKS_PER_SEC; // Registra o tempo de término

    free(numeros);

    if (encontrado) {
        return end_time - start_time;
    } else {
        return -1.0;
    }
}

// Função para realizar a classificação de elementos usando o algoritmo Insertion Sort
void insertion_sort(int *numeros, int tamanho) {
    for (int i = 1; i < tamanho; i++) {
        int chave = numeros[i];
        int j = i - 1;

        while (j >= 0 && numeros[j] > chave) {
            numeros[j + 1] = numeros[j];
            j--;
        }

        numeros[j + 1] = chave;
    }
}

// Função para realizar a classificação de elementos usando o algoritmo Bubble Sort
void bubble_sort(int *numeros, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        for (int j = 0; j < tamanho - i - 1; j++) {
            if (numeros[j] > numeros[j + 1]) {
                int temp = numeros[j];
                numeros[j] = numeros[j + 1];
                numeros[j + 1] = temp;
            }
        }
    }
}

// Função auxiliar para particionar o array para o Quick Sort
int particion(int *numeros, int baixo, int alto) {
    int pivo = numeros[alto];
    int i = (baixo - 1);

    for (int j = baixo; j <= alto - 1; j++) {
        if (numeros[j] < pivo) {
            i++;
            int temp = numeros[i];
            numeros[i] = numeros[j];
            numeros[j] = temp;
        }
    }

    int temp = numeros[i + 1];
    numeros[i + 1] = numeros[alto];
    numeros[alto] = temp;

    return (i + 1);
}

// Função para realizar a classificação de elementos usando o algoritmo Quick Sort
void quick_sort(int *numeros, int baixo, int alto) {
    if (baixo < alto) {
        int pivo = particion(numeros, baixo, alto);

        quick_sort(numeros, baixo, pivo - 1);
        quick_sort(numeros, pivo + 1, alto);
    }
}

int main() {
    char nome_arquivo[] = "numeros.txt";
    int quantidade;

    printf("Quantidade de números a gerar: ");
    scanf("%d", &quantidade);
    gerar_arquivo_numeros(nome_arquivo, quantidade);

    while (1) {
        printf("\nMenu de Operações:\n");
        printf("1. Operações de busca de elemento\n");
        printf("2. Operações de classificação de elementos (Insertion Sort, Bubble Sort, Quick Sort)\n");
        printf("3. Sair\n");
        printf("Escolha a operação (1/2/3): ");
        int escolha;
        scanf("%d", &escolha);

        if (escolha == 1) {
            int numero;
            printf("Digite o número a ser buscado: ");
            scanf("%d", &numero);

            double busca_linear_tempo = busca_linear(numero, nome_arquivo);
            double busca_sentinela_tempo = busca_sentinela(numero, nome_arquivo);
            double busca_binaria_tempo = busca_binaria(numero, nome_arquivo);

            if (busca_linear_tempo != -1.0) {
                printf("Tempo da busca linear: %f segundos\n", busca_linear_tempo);
            } else {
                printf("Número não encontrado na busca linear.\n");
            }

            if (busca_sentinela_tempo != -1.0) {
                printf("Tempo da busca sentinela: %f segundos\n", busca_sentinela_tempo);
            } else {
                printf("Número não encontrado na busca sentinela.\n");
            }

            if (busca_binaria_tempo != -1.0) {
                printf("Tempo da busca binária: %f segundos\n", busca_binaria_tempo);
            } else {
                printf("Número não encontrado na busca binária.\n");
            }
        } else if (escolha == 2) {
            FILE *arquivo = fopen(nome_arquivo, "r");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                exit(1);
            }

            int numeros[quantidade];
            int i = 0;
            int num;
            while (fscanf(arquivo, "%d", &num) != EOF) {
                numeros[i] = num;
                i++;
            }
            fclose(arquivo);

            int numeros_insertion[quantidade];
            int numeros_bubble[quantidade];
            int numeros_quick[quantidade];
            for (int j = 0; j < quantidade; j++) {
                numeros_insertion[j] = numeros[j];
                numeros_bubble[j] = numeros[j];
                numeros_quick[j] = numeros[j];
            }

            double start_time_insertion = (double)clock() / CLOCKS_PER_SEC;
            insertion_sort(numeros_insertion, quantidade);
            double end_time_insertion = (double)clock() / CLOCKS_PER_SEC;

            double start_time_bubble = (double)clock() / CLOCKS_PER_SEC;
            bubble_sort(numeros_bubble, quantidade);
            double end_time_bubble = (double)clock() / CLOCKS_PER_SEC;

            double start_time_quick = (double)clock() / CLOCKS_PER_SEC;
            quick_sort(numeros_quick, 0, quantidade - 1);
            double end_time_quick = (double)clock() / CLOCKS_PER_SEC;

            printf("Tempo do Insertion Sort: %f segundos\n", end_time_insertion - start_time_insertion);
            printf("Tempo do Bubble Sort: %f segundos\n", end_time_bubble - start_time_bubble);
            printf("Tempo do Quick Sort: %f segundos\n", end_time_quick - start_time_quick);
        } else if (escolha == 3) {
            break;
        } else {
            printf("Escolha uma opção. 1, 2 ou 3\n");
        }
    }

    return 0;
}
