#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include <windows.h>
#include "bucketsort.h"
#include "util.h"

#define MAX_NOMES 20000
#define MAX_NOMES_TAM 100

// Estrutura de dados para um bucket
struct Bucket {
    char **values;
    int count;
    int capacity;
};

// Inicializa um bucket
void initBucket(struct Bucket *bucket, int capacity) {
    bucket->values = (char **)malloc(sizeof(char *) * capacity);  // Aloca espaço para o vetor de strings
    bucket->count = 0;
    bucket->capacity = capacity;
}

// Adiciona um elemento a um bucket
void addValue(struct Bucket *bucket, char *value) {
    if (bucket->count == bucket->capacity) {
        bucket->capacity *= 2;
        bucket->values = (char **)realloc(bucket->values, sizeof(char *) * bucket->capacity);  // Realloc para aumentar a capacidade
    }
    bucket->values[bucket->count++] = value;  
}

// Comparar as strings, para usar no bucket sort
int compareStrings(const void *a, const void *b) {
    return strcasecmp(*(const char **)a, *(const char **)b);
}

// Ordenação principal BucketSort
void bucketSort(char **v, int n) {
    // Número de buckets
    int bucketCount = n;
    struct Bucket *buckets = (struct Bucket *)malloc(sizeof(struct Bucket) * bucketCount);

    // Inicializa cada bucket
    for (int i = 0; i < bucketCount; i++) {
        initBucket(&buckets[i], 5);
    }

    // Distribui os elementos para os buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = (int)(v[i][0] * bucketCount / 256); // Mapeamento para o bucket (usando o primeiro caractere do nome)
        addValue(&buckets[bucketIndex], v[i]);
    }

    // Ordena cada bucket individualmente
    for (int i = 0; i < bucketCount; i++) {
        qsort(buckets[i].values, buckets[i].count, sizeof(char *), compareStrings); // Usa qsort para ordenar as strings
    }

    // Combina todos os buckets no array original
    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        for (int j = 0; j < buckets[i].count; j++) {
            v[index++] = buckets[i].values[j];
        }
    }

    // Libera a memória dos buckets
    for (int i = 0; i < bucketCount; i++) {
        free(buckets[i].values);
    }
    free(buckets);
}

int menuBucketSort(){

// Endereça os arquivos locais
    char *nomes_copia = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\BucketSort\\CopiaParaOrdenar\\nomes_compostos_copia.txt";
    char *nomes_ordenados = "..\\ProjetoAPS\\AlgoritmosOrdenacao\\BucketSort\\CopiaOrdenada\\nomes_compostos_ordenado_bucket.txt";
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
    Sleep(500);  // Atraso para teste correr corretamente (500 milissegundos = 0.5 segundos)
    printf("\nIniciando a ordenacao dos elementos...\n");

// Ordena o vetor
   bucketSort(v, num_elementos);

// Calcula o tempo de execução
    gettimeofday(&end, NULL);
    double cpu_time_used = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    double sleep_time = 0.5;
    cpu_time_used -= sleep_time;

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