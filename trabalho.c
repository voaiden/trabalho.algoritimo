#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Protótipos das funções
void criarArquivoDados();
int lerDados(int v[]);
void salvarOrdenado(int v[], int tam);
void bubbleSort(int v[], int tam);
void selectionSort(int v[], int tam);
void alterarValor();

int main() {
    int opcao;
    int vetor[MAX];
    int tamanho = 0;

    do {
        printf("\n========================================\n");
        printf("    SISTEMA DE ORDENACAO E ARQUIVOS     \n");
        printf("========================================\n");
        printf("1. Criar e gravar dados desordenados\n");
        printf("2. Ler dados do arquivo\n");
        printf("3. Escolher ordenacao e salvar resultado\n");
        printf("4. Alterar um valor no arquivo e reordenar\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criarArquivoDados();
                break;
            case 2:
                tamanho = lerDados(vetor);
                if (tamanho > 0) {
                    printf("\nDados lidos com sucesso! Total de elementos: %d\n", tamanho);
                    printf("Valores: ");
                    for (int i = 0; i < tamanho; i++) {
                        printf("%d ", vetor[i]);
                    }
                    printf("\n");
                }
                break;
            case 3: {
                tamanho = lerDados(vetor);
                if (tamanho == 0) {
                    printf("\nArquivo 'dados.txt' vazio ou inexistente. Crie os dados primeiro!\n");
                    break;
                }
                
                int escolha;
                printf("\nEscolha o algoritmo de ordenacao:\n");
                printf("1. Bubble Sort\n");
                printf("2. Selection Sort\n");
                printf("Opcao: ");
                scanf("%d", &escolha);

                if (escolha == 1) {
                    bubbleSort(vetor, tamanho);
                    printf("\nOrdenado com Bubble Sort!\n");
                } else if (escolha == 2) {
                    selectionSort(vetor, tamanho);
                    printf("\nOrdenado com Selection Sort!\n");
                } else {
                    printf("\nOpcao invalida!\n");
                    break;
                }

                salvarOrdenado(vetor, tamanho);
                break;
            }
            case 4:
                alterarValor();
                break;
            case 5:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

void criarArquivoDados() {
    FILE *arq = fopen("dados.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }

    int valores[] = {45, 12, 89, 3, 25, 67, 34, 9, 50, 18};
    int qtd = 10;

    for (int i = 0; i < qtd; i++) {
        fprintf(arq, "%d\n", valores[i]);
    }

    fclose(arq);
    printf("\nArquivo 'dados.txt' criado com sucesso com valores desordenados!\n");
}

int lerDados(int v[]) {
    FILE *arq = fopen("dados.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo 'dados.txt'.\n");
        return 0;
    }

    int i = 0;
    while (i < MAX && fscanf(arq, "%d", &v[i]) == 1) {
        i++;
    }

    fclose(arq);
    return i;
}

void salvarOrdenado(int v[], int tam) {
    FILE *arq = fopen("ordenado.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar 'ordenado.txt'.\n");
        return;
    }

    for (int i = 0; i < tam; i++) {
        fprintf(arq, "%d\n", v[i]);
    }

    fclose(arq);
    
    printf("Valores ordenados salvos em 'ordenado.txt':\n");
    for (int i = 0; i < tam; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

void bubbleSort(int v[], int tam) {
    int aux;
    for (int i = 0; i < tam - 1; i++) {
        for (int j = 0; j < tam - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void selectionSort(int v[], int tam) {
    for (int i = 0; i < tam - 1; i++) {
        int min = i;
        for (int j = i + 1; j < tam; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            int aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

void alterarValor() {
    int v[MAX];
    int tam = lerDados(v);

    if (tam == 0) {
        printf("\nNenhum dado encontrado para alterar.\n");
        return;
    }

    printf("\nValores atuais no arquivo:\n");
    for (int i = 0; i < tam; i++) {
        printf("[%d] = %d\n", i, v[i]);
    }

    int indice, novoValor;
    printf("Digite o indice do elemento que deseja alterar (0 a %d): ", tam - 1);
    scanf("%d", &indice);

    if (indice < 0 || indice >= tam) {
        printf("Indice invalido!\n");
        return;
    }

    printf("Digite o novo valor: ");
    scanf("%d", &novoValor);

    v[indice] = novoValor;

    FILE *arq = fopen("dados.txt", "w");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo para atualizacao.\n");
        return;
    }
    for (int i = 0; i < tam; i++) {
        fprintf(arq, "%d\n", v[i]);
    }
    fclose(arq);

    printf("\nValor alterado com sucesso em 'dados.txt'!\n");

    bubbleSort(v, tam);
    salvarOrdenado(v, tam);
}