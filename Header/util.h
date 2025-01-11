#ifndef UTIL_H
#define UTIL_H

//Funções
void swap(char **v, char **v2);
void inicialMaiuscula(char *str);
int lerArquivo(char *nomes_copia, char **v);
void escreverArquivo(char *ordenacao, char **v, int num_elementos);
int criarCopiaArquivo(const char *arquivo_original, const char *arquivo_copia);
void adicionarNome(char *nomes_copia);
void liberarMemoria(char **v, int num_elementos);

#endif