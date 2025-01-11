#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMES 10000
#define MAX_NOMES_TAM 100

// Troca as posições dos elementos
void swap (char v[MAX_NOMES_TAM], char v2[MAX_NOMES_TAM]){ 
    char temp[MAX_NOMES_TAM];
    strcpy(temp, v);
    strcpy(v, v2);
    strcpy(v2, temp);
}

// Particiona o vetor e define o "Pivot"
int particao(char v[][MAX_NOMES_TAM], int m, int n, int ordem) { 
    char pivot[MAX_NOMES_TAM];
    strcpy(pivot, v[n]); 
    int i = (m - 1);

    for (int j = m; j <= n - 1; j++) {
        // Condição de ordenação com base no parâmetro 'ordem'
        if ((ordem == 1 && strcmp(v[j], pivot) <= 0) ||  // Crescente
            (ordem == -1 && strcmp(v[j], pivot) >= 0)) {  // Decrescente
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[n]);
    return (i + 1);
}

// Ordena em "QuickSort"
void quicksort_completo(char v[][MAX_NOMES_TAM], int primeiro, int ultimo, int ordem) {
    if (primeiro < ultimo) {
        int q = particao(v, primeiro, ultimo, ordem);
        quicksort_completo(v, primeiro, q - 1, ordem);
        quicksort_completo(v, q + 1, ultimo, ordem);
    }
}
void quicksort_metade(char v[][MAX_NOMES_TAM], int primeiro, int ultimo, int ordem) {
    int meio = (primeiro + ultimo) / 2;
    // Ordena a primeira metade de forma completa
    quicksort_completo(v, primeiro, meio, ordem);
    }

// Abre e lê o arquivo
int lerArquivo(char *nomes_compostos, char v[MAX_NOMES][MAX_NOMES_TAM]) {

    printf("\nTentando abrir o arquivo: %s\n", nomes_compostos); // Mensagem de depuração
    FILE *file = fopen(nomes_compostos, "r");
    
    if (file == NULL) {
        printf("\nErro Leitura: Não foi possível abrir o arquivo %s.\n", nomes_compostos);
        return -1;
    }
    int i = 0;
    while (fgets(v[i], MAX_NOMES_TAM, file) != NULL && i < MAX_NOMES) {
        i++; 
    }
    fclose(file);
    printf("\nLeitura do arquivo concluida. Total de elementos lidos: %d\n", i); // Mensagem de depuração
    return i;
}
// Escreve os elementos ordenados em um arquivo
void escreverArquivo(char *ordenado_quick, char v[MAX_NOMES][MAX_NOMES_TAM], int num_elementos) {
    FILE *file = fopen(ordenado_quick, "w");

    if (file == NULL) {
        printf("\nErro Escrita: Nao foi possivel criar o arquivo %s.\n", ordenado_quick);
        return;
    }
    for (int j = 0; j < num_elementos; j++) {
        fprintf(file, "%s", v[j]); // `fgets` já adiciona uma nova linha, então não é necessário usar `\n`
    }

    fclose(file);
    printf("\nElementos ordenados foram salvos em %s\n", ordenado_quick); // Mensagem de confirmação
}
// Cria uma cópia do arquivo
int criarCopiaArquivo(const char *arquivo_original, const char *arquivo_copia) {
    FILE *origem = fopen(arquivo_original, "r");
    if (origem == NULL) {
        printf("\nErro Copia: Nao foi possivel abrir o arquivo original %s para copiar.\n", arquivo_original);
        return -1;
    }
    FILE *copia = fopen(arquivo_copia, "w");
    if (copia == NULL) {
        printf("\nErro Copia: Nao foi possivel criar o arquivo de copia %s.\n", arquivo_copia);
        fclose(origem);
        return -1;
    }
    char buffer[1024];
    size_t bytesLidos;
    while ((bytesLidos = fread(buffer, 1, sizeof(buffer), origem)) > 0) {
        fwrite(buffer, 1, bytesLidos, copia);
    }
    fclose(origem);
    fclose(copia);
    printf("\nCopia do arquivo '%s' criada com sucesso como '%s'.\n", arquivo_original, arquivo_copia);
    return 0;
}

int main () {
    char v[MAX_NOMES][MAX_NOMES_TAM];
    int num_elementos;
    int opcao = 0;
    int ordem;
    char *nomes_compostos = "..\\txtDesordenados\\AleatorioCaso10k.txt";
    char *nomes_copia = "..\\txtDesordenados\\SemiOrdemCaso10k.txt";
    num_elementos = lerArquivo("..\\txtDesordenados\\AleatorioCaso10k.txt", v);
    
    // Verifica erro e termina o programa caso ocorra um erro na leitura do arquivo
    if (num_elementos < 0) {
        printf("\nErro Leitura Copia: Falha ao ler o arquivo.\n");
        return 1; 
    }
    // Verifica erro ao copiar o arquivo
    if (criarCopiaArquivo(nomes_compostos, nomes_copia) < 0) {
    printf("\nErro Copia: Nao foi possivel criar a copia do arquivo. Encerrando o programa.\n");
    return 1;
}
while (1) {
        printf("\nQual caso deseja criar?\n");
        printf("1 - Arquivo Semi-Ordenado \n");
        printf("2 - Arquivo Decrescente \n");
        scanf("\n%d", &opcao);
        getchar(); // Limpa o buffer de entrada após scanf

        if (opcao == 1){
            ordem = 1;
            printf("\nIniciando arquivo Semi-Ordenado \n"); //Depuração
            quicksort_metade(v, 0, num_elementos - 1, ordem);
            escreverArquivo("..\\txtDesordenados\\SemiOrdemCaso10k.txt", v, num_elementos);
            break;
        } else if (opcao == 2) {
            ordem = -1;
            printf("\nIniciando arquivo Decrescente \n"); //Depuração
            quicksort_completo(v, 0, num_elementos - 1, ordem);
            escreverArquivo("..\\txtDesordenados\\PiorCaso10k.txt", v, num_elementos);
            break;
        }
        else {
            printf("\nOpcao invalida. Por favor, escolha entre 1 e 2.\n\n");
        }
}
}
