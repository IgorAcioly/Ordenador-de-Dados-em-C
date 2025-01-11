#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define QTD_NOMES 200 
#define QTD_NOMES_GERAR 10000
#define TAM_NOME 100 
#define TEMPO_MAXIMO 5

// Função para verificar nomes repetidos
int duplicado(char** nomes_gerados, int count, const char* nomes_compostos) {
    for (int j = 0; j < count; j++) {
        if (strcmp(nomes_gerados[j], nomes_compostos) == 0) {
            return 1; 
        }
    }
    return 0; 
}

int main() {
    time_t t_inicio, t_atual;
    double t_decorrido;
    int success = 1;
// Alocação dinâmica para as listas
    char** nomes_brasil = malloc(QTD_NOMES * sizeof(char*));
    char** nomes_japao = malloc(QTD_NOMES * sizeof(char*));
    const char* caminho_relativo = "..\\txtDesordenados\\nomes_compostos_aleatorios.txt";

    if (nomes_brasil == NULL || nomes_japao == NULL) {
        fprintf(stderr, "Erro ao alocar memória para listas de nomes.\n");
        return 1;
    }
// Listas nomes brasileiros
const char* lista_brasil[] = {
    "Lucas", "Ana", "Pedro", "Maria", "Gabriel", "Juliana", "Rafael", "Fernanda", "Vinícius", "Cláudia",
    "Carlos", "Joana", "Samuel", "Camila", "Diego", "Henrique", "Tatiane", "Ricardo", "Mariana", "Gustavo",
    "Evelyn", "Felipe", "Aline", "Beatriz", "Victor", "Giovanna", "Isabela", "Renata", "Paulo", "Rita",
    "Roberto", "Raquel", "Sérgio", "Luana", "Marcelo", "Natália", "André", "Leonardo", "Silvia", "Jéssica",
    "Marcela", "Vanessa", "Bruno", "Fábio", "Luciana", "Thiago", "Clara", "Adriana", "Julio", "Fátima",
    "Daniele", "Juliano", "Cecilia", "Eliane", "Milena", "Monique", "Thais", "Sandro", "Jorge", "Renato",
    "Sofia", "Marcos", "Daniel", "Michele", "Karla", "Ivo", "Luan", "Matheus", "Raissa", "Tânia",
    "Priscila", "Emanuel", "Gabriela", "Danilo", "Bruna", "Igor", "Sara", "Cláudio", "César", "Afonso",
    "Diana", "Patrícia", "Isadora", "Karina", "Hugo", "Ariane", "Kelly", "Sandra", "Nelson", "Guilherme",
    "Pablo", "Catherine", "Adelaide", "Sophia", "Giovani", "José", "Marcia", "Tainara", "Lia", "Angela",
    "Lorena", "Eduardo", "Alice", "Bernardo", "Helena", "Rodrigo", "Letícia", "Otávio", "Viviane", "Alexandre",
    "Marta", "Caio", "Livia", "Murilo", "Tatiana", "João", "Bárbara", "Caíque", "Estela", "Renan",
    "Flávia", "Arthur", "Carolina", "Alfredo", "Elisa", "Cristiano", "Olivia", "Augusto", "Bianca", "Rogério",
    "Lúcia", "Erick", "Regina", "Leandro", "Raissa", "Fabrício", "Adriana", "Aldo", "Glória", "Heloísa",
    "Davi", "Larissa", "Emerson", "Mirela", "Tomás", "Erica", "Alan", "Marlene", "Alana", "Henrique",
    "Ronaldo", "Aparecida", "Cássio", "Marli", "Paula", "Jonathan", "Debora", "Brenda", "Rubens", "Heloise",
    "Aline", "Ruan", "Jeferson", "Melissa", "Ciro", "Renilda", "Vera", "Hilda", "Jair", "Carla",
    "Natan", "Eliane", "Mariah", "Tomás", "Lauro", "Darlene", "Orlando", "Jaqueline", "Geraldo", "Taís",
    "Manoel", "Patrícia", "Horácio", "Lourdes", "Giane", "Feliciano", "Evandro", "Letícia", "Sônia", "Clovis",
    "Luiz", "Noemi", "Hermes", "Celina", "Wesley", "Brígida", "Valdir", "Vivian", "Josiane", "Tatiana"
};
    // Lista nomes japoneses
   const char* lista_japao[] = {
    "Haruto", "Yuki", "Sakura", "Hana", "Ren", "Riku", "Yui", "Sora", "Kaito", "Miku",
    "Shin", "Rina", "Hiro", "Nori", "Hikaru", "Masaki", "Aki", "Taro", "Kazuki", "Natsuki",
    "Akira", "Keiko", "Yoko", "Rei", "Takumi", "Haruki", "Ayumi", "Yuto", "Miyuki", "Haruna",
    "Kenta", "Shota", "Ryota", "Nana", "Yoshi", "Saki", "Mio", "Hanae", "Kazuya", "Daiki",
    "Mai", "Erika", "Ryu", "Yuuki", "Ryo", "Hinata", "Yoshiko", "Katsu", "Noboru", "Reiko",
    "Shinobu", "Kyou", "Kazuki", "Miyu", "Hana", "Chiyo", "Akemi", "Keisuke", "Miki", "Hikaru",
    "Jin", "Sayaka", "Toshi", "Naoki", "Yuuma", "Renji", "Nobu", "Minato", "Fumiko", "Satoshi",
    "Tadashi", "Aoi", "Emi", "Yuuki", "Shou", "Riku", "Hiroshi", "Kei", "Taiga", "Mizuki",
    "Kyouko", "Haruka", "Katsuki", "Takashi", "Koji", "Rika", "Sōma", "Kazuma", "Kyoko", "Yukio",
    "Kota", "Kazuhiko", "Megumi", "Yoko", "Rina", "Shōko", "Yūma", "Shizuku", "Riki", "Shōta",
    "Akane", "Kenta", "Satsuki", "Rikuya", "Ayane", "Shougo", "Hanae", "Tsubaki", "Minato",
    "Akihiko", "Yuina", "Ryohei", "Erina", "Hayato", "Kirika", "Souta", "Kouki", "Misaki",
    "Hikaru", "Kaoru", "Chika", "Taichi", "Yasuo", "Rina", "Nao", "Natsuki", "Kou", "Ryoichi",
    "Ami", "Haruki", "Miyu", "Kazuma", "Seiya", "Sae", "Nobu", "Atsumi", "Hiroyuki", "Masato",
    "Sakura", "Hikaru", "Yoshiki", "Sayaka", "Hajime", "Renji", "Yuriko", "Kiyoshi", "Rika",
    "Takara", "Yukari", "Taiga", "Hiroshi", "Mikio", "Sayuri", "Tomoya", "Keita", "Airi",
    "Hikaru", "Yukino", "Kazuki", "Ryo", "Kazuhiro", "Yumi", "Shun", "Minoru", "Masashi",
    "Reo", "Keisuke", "Kiyomi", "Yuuto", "Miki", "Nana", "Yuta", "Mikoto", "Aiko", "Rika",
    "Natsume", "Sora", "Kenta", "Hiro", "Yoshito", "Megumi", "Atsushi", "Kouki", "Yuuki",
    "Haruka", "Yuki", "Kazue", "Masumi", "Akira", "Saki", "Ryohei", "Keiko", "Natsuki",
    "Shinobu", "Ren", "Haru", "Toshi", "Mizuho", "Tomoka", "Rei"
};

// Preenche os vetores com os nomes baseado nas listas
    for (int i = 0; i < QTD_NOMES; i++) {
        nomes_brasil[i] = malloc((strlen(lista_brasil[i % (sizeof(lista_brasil) / sizeof(lista_brasil[0]))]) + 1) * sizeof(char));
        strcpy(nomes_brasil[i], lista_brasil[i % (sizeof(lista_brasil) / sizeof(lista_brasil[0]))]);

        nomes_japao[i] = malloc((strlen(lista_japao[i % (sizeof(lista_japao) / sizeof(lista_japao[0]))]) + 1) * sizeof(char));
        strcpy(nomes_japao[i], lista_japao[i % (sizeof(lista_japao) / sizeof(lista_japao[0]))]);
    }

    srand(time(NULL)); // Gerador de números aleatórios

// Abre o arquivo para escrita
    FILE *file = fopen(caminho_relativo, "w"); 
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita.\n");
        free(nomes_brasil); 
        free(nomes_japao);
        return 1;
    }
    printf("\nAbrindo arquivo\n\n");

// Analisa as combinações já geradas, evitando a repetição de nomes
    char** nomes_gerado = malloc(QTD_NOMES_GERAR * sizeof(char*));
    int count = 0;
    t_inicio = time(NULL);

// Gera nomes compostos e escrevendo no arquivo
    while (count < QTD_NOMES_GERAR ) {
        t_atual = time(NULL);
        t_decorrido = difftime(t_atual, t_inicio);

    // Interrompe o laço se o tempo máximo for excedido 
        if (t_decorrido >= TEMPO_MAXIMO) {
            printf("Erro: Tempo de execucao excedido!\n");
            success = 0;
            break; 
        }
    // Cria a combinação
        int index_brasil = rand() % QTD_NOMES;
        int index_japao = rand() % QTD_NOMES;

        char nome_composto[TAM_NOME];
        snprintf(nome_composto, TAM_NOME, "%s %s", nomes_brasil[index_brasil], nomes_japao[index_japao]);
        if (nome_composto[0] != '\0' && strspn(nome_composto, " ") != strlen(nome_composto)) {
        // Verifica se já foi gerado
            if (!duplicado(nomes_gerado, count, nome_composto)) {
                fprintf(file, "%s\n", nome_composto);
                nomes_gerado[count++] = strdup(nome_composto); // Armazenar a combinação
            }
        }
    }
// Fecha o arquivo
    fclose(file);

    if (success == 1){
        printf("Nomes compostos gerados e salvos em 'nomes_compostos_aleatorios.txt'.\n");
    }

// Libera a memória
    for (int i = 0; i < count; i++) {
        free(nomes_gerado[i]); 
    }
    free(nomes_gerado);
    free(nomes_brasil);
    free(nomes_japao);

    return 0;

}
