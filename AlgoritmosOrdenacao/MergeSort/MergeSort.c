#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "mergesort.h"
#include "util.h"

#define MAX_NOMES 20000
#define MAX_NOMES_TAM 100

// Função de Mesclagem para o Merge Sort
void merge(char **v, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Criar arrays temporários dinâmicos
    char **leftArr = (char **)malloc(n1 * sizeof(char *));
    char **rightArr = (char **)malloc(n2 * sizeof(char *));
    
    if (leftArr == NULL || rightArr == NULL) {
        printf("Erro de alocação de memória!\n");
        return;
    }

    // Aloca memória para cada string dentro dos arrays temporários
    for (int i = 0; i < n1; i++) {
        leftArr[i] = (char *)malloc(MAX_NOMES_TAM * sizeof(char));
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = (char *)malloc(MAX_NOMES_TAM * sizeof(char));
    }

    // Copia os dados para os arrays temporários
    for (int i = 0; i < n1; i++) {
        strcpy(leftArr[i], v[left + i]);
    }
    for (int j = 0; j < n2; j++) {
        strcpy(rightArr[j], v[mid + 1 + j]);
    }

    // Mescla os arrays temporários de volta ao array original
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(leftArr[i], rightArr[j]) <= 0) {
            strcpy(v[k], leftArr[i]);
            i++;
        } else {
            strcpy(v[k], rightArr[j]);
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de leftArr[]
    while (i < n1) {
        strcpy(v[k], leftArr[i]);
        i++;
        k++;
    }

    // Copiar os elementos restantes de rightArr[]
    while (j < n2) {
        strcpy(v[k], rightArr[j]);
        j++;
        k++;
    }

    for (int i = 0; i < n1; i++) {
        free(leftArr[i]);
    }
    for (int i = 0; i < n2; i++) {
        free(rightArr[i]);
    }
    free(leftArr);
    free(rightArr);
}

// Função Recursiva Merge Sort
void mergeSort(char **v, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Encontra o meio

        mergeSort(v, left, mid);  
        mergeSort(v, mid + 1, right); 
        merge(v, left, mid, right);  // Mescla as duas metades ordenadas
    }
}

void mergeRadix(char **v, int left, int mid, int right, int exp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++)
        L[i] = v[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = v[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        // Comparar os caracteres na posição `exp` de cada string
        if (L[i][exp] <= R[j][exp]) {
            v[k] = L[i];
            i++;
        } else {
            v[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSortRadix(char **v, int left, int right, int exp) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Encontra o meio

        mergeSortRadix(v, left, mid, exp);  
        mergeSortRadix(v, mid + 1, right,exp); 
        mergeRadix(v, left, mid, right, exp);  // Mescla as duas metades ordenadas
    }
}

int menuMergeSort() {
   
// Endereça os arquivos locais
    char *nomes_copia = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\MergeSort\\CopiaParaOrdenar\\nomes_compostos_copia.txt";
    char *nomes_ordenados = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\MergeSort\\CopiaOrdenada\\nomes_compostos_ordenado_merge.txt";
    int num_elementos;
    int opcao = 0;
    int opcaoTamanho,opcaoCaso;
    char **v = (char **)malloc(MAX_NOMES * sizeof(char *));

    for (int i = 0; i < MAX_NOMES; i++) {
        v[i] = (char *)malloc(MAX_NOMES_TAM * sizeof(char));  // Aloca memória para cada string
    }

// Menu para escolher o tamanho do arquivo
    while (1) {
        printf("\nDeseja ordenar qual tamanho de arquivo?\n");
        printf("1 - Array Menor (1.000 Elementos)\n");
        printf("2 - Array Maior (10.000 Elementos)\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcaoTamanho);
        getchar(); // Limpa o buffer de entrada após scanf

        if (opcaoTamanho == 1 || opcaoTamanho == 2) {
                // Menu para escolher o caso a ser testado
                printf("\nQual caso deseja testar?\n");
                printf("1 - Analisar 'txt' Semi-Ordenado\n");
                printf("2 - Analisar 'txt' Aleatorio\n");
                printf("3 - Analisar 'txt' Decrescente\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcaoCaso);
                getchar();

                if (opcaoCaso == 1) {
                    if (opcaoTamanho == 1) {
                        if (criarCopiaArquivo("..\\ProjetoAPS\\ArquivosDesordenados\\txtDesordenados\\SemiOrdemCaso1k.txt", nomes_copia) < 0) {
                            printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
                            return 1;
                        }
                    } else {
                        if (criarCopiaArquivo("..\\ProjetoAPS\\ArquivosDesordenados\\txtDesordenados\\SemiOrdemCaso10k.txt", nomes_copia) < 0) {
                            printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
                            return 1;
                        }
                    }
                } else if (opcaoCaso == 2) {
                    if (opcaoTamanho == 1) {
                        if (criarCopiaArquivo("..\\ProjetoAPS\\ArquivosDesordenados\\txtDesordenados\\AleatorioCaso1k.txt", nomes_copia) < 0) {
                            printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
                            return 1;
                        }
                    } else {
                        if (criarCopiaArquivo("..\\ProjetoAPS\\ArquivosDesordenados\\txtDesordenados\\AleatorioCaso10k.txt", nomes_copia) < 0) {
                            printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
                            return 1;
                        }
                    }
                } else if (opcaoCaso == 3) {
                    if (opcaoTamanho == 1) {
                        if (criarCopiaArquivo("..\\ProjetoAPS\\ArquivosDesordenados\\txtDesordenados\\DecrescenteCaso1k.txt", nomes_copia) < 0) {
                            printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
                            return 1;
                        }
                    } else {
                        if (criarCopiaArquivo("..\\ProjetoAPS\\ArquivosDesordenados\\txtDesordenados\\DecrescenteCaso10k.txt", nomes_copia) < 0) {
                            printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
                            return 1;
                        }
                    }
                } else {
                    printf("\nEscolha uma opcao valida para o caso!\n");
                    continue; //Reinicia o laço
                }
                break; // Encerra o loop quando a escolha for válida
            } else {
                printf("\nEscolha uma opcao valida para o tamanho do arquivo!\n");
            }
    }


// Menu para adicionar nome
    while (1) {
        printf("\nDeseja adicionar um nome ao arquivo?\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) { 
            adicionarNome(nomes_copia);
            num_elementos = lerArquivo(nomes_copia, v);
            printf("Numero de elementos lidos apos adicionar o nome: %d\n", num_elementos);
            break;
        } else if (opcao == 2) {
            break;
        } else {
            printf("\nOpcao invalida. Escolha entre 1 e 2.\n");
        }
    }

    num_elementos = lerArquivo(nomes_copia, v); 

    if (num_elementos < 0) {
        printf("\nErro Leitura Copia: Falha ao ler o arquivo.\n");
        return 1; 
    }
    
 // Medição precisa do tempo de execução
    struct timeval start, end;
    gettimeofday(&start, NULL);

    printf("\nIniciando a ordenacao dos elementos...\n");

// Ordena o vetor
    mergeSort(v, 0, num_elementos - 1);

// Calcula o tempo de execução
    gettimeofday(&end, NULL);
    double cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
  
// Escreve os elementos ordenados em um novo arquivo
    escreverArquivo(nomes_ordenados, v, num_elementos);

// Exibe o tempo de execução
    printf("\n+--------------------------------+--------------------------------+\n");
    printf("| Tarefa                         | Tempo de Execucao (segundos)   |\n");
    printf("+--------------------------------+--------------------------------+\n");
    printf("| Ordenacao de nomes compostos   | %.6f                       |\n", cpu_time_used);
    printf("+--------------------------------+--------------------------------+\n");
    
    liberarMemoria(v, num_elementos);
    return 0;
}
