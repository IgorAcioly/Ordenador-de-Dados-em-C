#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "quicksort.h"
#include "util.h"

#define MAX_NOMES 20000
#define MAX_NOMES_TAM 100


// Escolhe o pivô com a mediana do tamanho do vetor
int medianaDeTres(char **v, int m, int n) {
    int meio = (m + n) / 2;
    if (strcmp(v[m], v[meio]) > 0) {
        swap(&v[m], &v[meio]);
    }
    if (strcmp(v[m], v[n]) > 0) {
        swap(&v[m], &v[n]);
    }
    if (strcmp(v[meio], v[n]) > 0) {
        swap(&v[meio], &v[n]);
    }
    return meio;  // Retorna o índice da mediana
}

// Alterar a função particao para usar a mediana de três como pivô
int particao(char **v, int m, int n) {
    int pivotIndex = medianaDeTres(v, m, n);
    char *pivot = (char *)malloc((strlen(v[pivotIndex]) + 1) * sizeof(char));
    strcpy(pivot, v[pivotIndex]);
    swap(&v[pivotIndex], &v[n]);  // Troca a mediana com o último elemento
    int i = m - 1;
    for (int j = m; j < n; j++) {
        if (strcmp(v[j], pivot) <= 0) {
            i++;
            swap(&v[i], &v[j]);
        }
    }
    swap(&v[i + 1], &v[n]);
    free(pivot);
    return i + 1;
}

// Ordena em "QuickSort"
void quickSort (char **v, int primeiro, int ultimo){
    if (primeiro < ultimo) {
        int q = particao(v, primeiro, ultimo);
        quickSort(v, primeiro, q - 1); 
        quickSort(v, q + 1, ultimo); 
    }
}

int menuQuickSort(){
// Endereça os arquivos locais
    char *nomes_copia = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\QuickSort\\CopiaParaOrdenar\\nomes_compostos_copia.txt";
    char *nomes_ordenados = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\QuickSort\\CopiaOrdenada\\nomes_compostos_ordenado_quick.txt";
    int num_elementos = 0;
    int opcao = 0;
    int opcaoTamanho = 0;
    int opcaoCaso = 0;
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

    printf("Elementos lidos %d",num_elementos);
    printf("\nIniciando a ordenacao dos elementos...\n");

// Ordena o vetor
    quickSort(v, 0, num_elementos - 1);

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


