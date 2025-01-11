#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "heapsort.h"
#include "util.h"

#define MAX_NOMES 20000
#define MAX_NOMES_TAM 100
#define MAX_SIZE 20000 // Tamanho do heap


// Função heapify para ajustar o heap (max-heap)
void heapifyMIN(char **v, int n, int i) {
    int smallest = i; // Inicializa o menor como raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Verifica se o filho esquerdo é menor que a raiz
    if (left < n && strcmp(v[left], v[smallest]) < 0) {
        smallest = left;
    }

    // Verifica se o filho direito é menor que o menor até agora
    if (right < n && strcmp(v[right], v[smallest]) < 0) {
        smallest = right;
    }

    // Se o menor não for a raiz, troca e faz heapify na subárvore
    if (smallest != i) {
        swap(&v[i], &v[smallest]);
        heapifyMIN(v, n, smallest); // Recursivamente heapify na subárvore afetada
    }
}

// Função para ordenar o vetor usando o algoritmo Heap Sort
void heapSortMIN(char **v, int n) {
    // Construção do min-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMIN(v, n, i);
    }

    // Remove elementos do heap
    for (int i = n - 1; i > 0; i--) {
        swap(&v[0], &v[i]); // Troca a raiz (menor elemento) com o último
        heapifyMIN(v, i, 0); // Reorganiza o heap para manter a propriedade min-heap
    }
}

// Função heapify para ajustar o heap (max-heap)
void heapifyMAX(char **v, int n, int i) {
    int largest = i; // Inicializa o maior como raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Verifica se o filho esquerdo é maior que a raiz
    if (left < n && strcmp(v[left], v[largest]) > 0) {
        largest = left;
    }

    // Verifica se o filho direito é maior que o maior até agora
    if (right < n && strcmp(v[right], v[largest]) > 0) {
        largest = right;
    }

    // Se o maior não for a raiz, troca e faz heapify na subárvore
    if (largest != i) {
        swap(&v[i], &v[largest]);
        heapifyMAX(v, n, largest); // Recursivamente heapify na subárvore afetada
    }
}

// Ordenação princiapl Heap Sort
void heapSortMAX(char **v, int n) {
    // Construção do max-heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMAX(v, n, i);
    }

    // Remove elementos do heap
    for (int i = n - 1; i > 0; i--) {
        swap(&v[0], &v[i]); // Troca a raiz (maior elemento) com o último
        heapifyMAX(v, i, 0); // Reorganiza o heap para manter a propriedade max-heap
    }
}

int menuHeapSort(){
     
// Endereça os arquivos locais
    char *nomes_copia = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\HeapSort\\CopiaParaOrdenar\\nomes_compostos_copia_heap.txt";
    char *nomes_ordenados = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\HeapSort\\CopiaOrdenada\\nomes_compostos_ordenado_heap.txt";
    int num_elementos;
    int opcao = 0;
    int opcaoTamanho,opcaoCaso;
    int tipoHeap;
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

    while(1){
        printf("\nEscolha qual tipo de HeapSort:\n");
        printf("1 - HeapSort MAX\n");
        printf("2 - HeapSort MIN\n");
        printf("Digite sua opcao:");
        scanf("%d",&tipoHeap);

        if (tipoHeap == 1 || tipoHeap == 2) {
            break;
        } else {
            printf("\nOpcao invalida. Escolha entre 1 e 2.\n");
        }
    }
    // Início da execução
    struct timeval start, end;
    gettimeofday(&start, NULL);

    if (tipoHeap == 1) {
        printf("\nIniciando a ordenacao HeapSort MAX:\n");
        heapSortMAX(v, num_elementos);
    } else if (tipoHeap == 2) {
        printf("\nIniciando a ordenacao HeapSort MIN:\n");
        heapSortMIN(v, num_elementos);
    }
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

 