#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_NOMES 20000
#define MAX_NOMES_TAM 100


//Funções padrão dos "menus" de cada algoritmo de ordenação
void swap(char **v, char **v2) { // Função Troca as posições dos elementos
    char *temp = (char *)malloc(MAX_NOMES_TAM * sizeof(char));
        if (temp == NULL) {
        printf("Erro ao alocar memória para a troca.\n");
        return; // Se não conseguir alocar memória, retorna sem fazer a troca
    }
    strcpy(temp, *v);  
    strcpy(*v, *v2);  
    strcpy(*v2, temp);
    free(temp);

}

void inicialMaiuscula(char *str) {
    int i = 0;
    int inWord = 0;

    while (str[i] != '\0') {
        if (isalpha(str[i])) {  // Se o caractere for uma letra
            if (!inWord) {  
                str[i] = toupper(str[i]);  // Torna a letra maiúscula
                inWord = 1; 
            } else {
                str[i] = tolower(str[i]);  // Torna a letra minúscula
            }
        } else {
            inWord = 0; 
        }
        i++;
    }
}

int lerArquivo(char *nomes_copia, char **v) {

    printf("\nAbrir o arquivo: %s\n", nomes_copia); 

    FILE *file = fopen(nomes_copia, "r");
    if (file == NULL) {
        printf("\nErro Leitura: Não foi possível abrir o arquivo %s.\n", nomes_copia);
        return -1;
    }

    int i = 0;
    char linha[MAX_NOMES_TAM];
    while (fgets(linha, sizeof(linha), file)) {
        strcpy(v[i], linha);
        i++;
    }

    fclose(file);
    return i;
}

void escreverArquivo(char *ordenacao, char **v, int num_elementos) {

    FILE *file = fopen(ordenacao, "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo %s.\n", ordenacao);
        return;
    }

    for (int j = 0; j < num_elementos; j++) {
        fprintf(file, "%s", v[j]);
    }
    printf("\nElementos ordenados foram salvos em %s\n", ordenacao); 
    fclose(file);
}

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

    size_t buffer_size = 1024;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));  // Aloca memória para o buffer

    size_t bytesLidos;
        while ((bytesLidos = fread(buffer, 1, buffer_size, origem)) > 0) {
        fwrite(buffer, 1, bytesLidos, copia);
        }   

    fclose(origem);
    fclose(copia);
    free(buffer);

    printf("\nCopia do arquivo '%s' criada com sucesso como '%s'.\n", arquivo_original, arquivo_copia);
    return 0;
}

void adicionarNome(char *nomes_copia) {

    char *nome = (char *)malloc(MAX_NOMES_TAM * sizeof(char));

    printf("\nDigite o nome que deseja adicionar: ");
    fgets(nome, MAX_NOMES_TAM, stdin);
    inicialMaiuscula(nome);

    FILE *file = fopen(nomes_copia, "a");
    if (file == NULL) {
        printf("\nErro Inserscao: Nao foi possivel abrir o arquivo %s.\n", nomes_copia);
        free(nome);
        return;
    }
    fprintf(file, "%s", nome); 

    fflush(file);
    fclose(file);
    free(nome);

    printf("\nNome '%s' adicionado ao arquivo '%s'.\n", nome, nomes_copia);
}

void liberarMemoria(char **v, int num_elementos) {
    for (int i = 0; i < num_elementos; i++) {
        free(v[i]);
    }
    free(v);
}
