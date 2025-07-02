#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TENTATIVAS 6

void registrar_vitoria(const char nome[]);
char remove_acento(char c);
void normalizar(char s[]);
char* escolher_palavra_aleatoria(const char *arquivo_tema);
void mostrar_feedback(const char tentativa[], const char palavra[]);


int main() {
    srand((unsigned int)time(NULL));
    char nome1[50], nome2[50];
    int modo = 0;
    while (modo != 1 && modo != 2) {
        printf("Escolha o modo de jogo:\n1- Sozinho contra a máquina\n2- Em dupla\n> ");
        if (scanf("%d", &modo) != 1) {
            while (getchar() != '\n'); // Limpa buffer
            modo = 0;
        }
        getchar();
    }

    if (modo == 1) {
        printf("Digite seu nome: ");
        fgets(nome1, sizeof nome1, stdin);
        nome1[strcspn(nome1, "\n")] = '\0';
    } else {
        printf("Digite o nome do Jogador 1 (quem adivinha): ");
        fgets(nome1, sizeof nome1, stdin);
        nome1[strcspn(nome1, "\n")] = '\0';
        printf("Digite o nome do Jogador 2 (quem escolhe a palavra): ");
        fgets(nome2, sizeof nome2, stdin);
        nome2[strcspn(nome2, "\n")] = '\0';
    }

    printf("Escolha um tema:\n1- Paises\n2- Comidas\n3- Objetos\n4- Filmes/Séries\n> ");
    int tema = 0;
    while (tema < 1 || tema > 4) {
        if (scanf("%d", &tema) != 1) {
            while (getchar() != '\n');
            tema = 0;
        }
        getchar();
    }

    char arquivo_tema[100];
    if (tema == 1) strcpy(arquivo_tema, "paises.txt");
    else if (tema == 2) strcpy(arquivo_tema, "comidas.txt");
    else if (tema == 3) strcpy(arquivo_tema, "objetos.txt");
    else strcpy(arquivo_tema, "filmes_series.txt");

    char palavra[100];
    if (modo == 1) {
        strcpy(palavra, escolher_palavra_aleatoria(arquivo_tema));
    } else {
        printf("%s, digite a palavra dentro do tema: ", nome2);
        fgets(palavra, sizeof palavra, stdin);
        palavra[strcspn(palavra, "\n")] = '\0';
        printf("\033[1A\033[2K\r");
    }

    normalizar(palavra);
    int tentativas = MAX_TENTATIVAS;
    int acertou = 0;
    while (tentativas > 0 && !acertou) {
        char tentativa[100];
        printf("\n%s, digite uma palavra com %zu letras (desconsidere espaços): ", nome1, strlen(palavra));
        fgets(tentativa, sizeof tentativa, stdin);
        tentativa[strcspn(tentativa, "\n")] = '\0';
        normalizar(tentativa);
        if (strlen(tentativa) != strlen(palavra)) {
            printf("A palavra deve ter %zu letras!\n", strlen(palavra));
            continue;
        }
        mostrar_feedback(tentativa, palavra);
        if (strcmp(tentativa, palavra) == 0) {
            acertou = 1;
        } else {
            tentativas--;
            printf("Tentativas restantes: %d\n", tentativas);
        }
    }

    if (acertou) {
        printf("Parabéns! Você acertou!\n");
        registrar_vitoria(nome1);
    } else {
        printf("Que pena! A palavra era: %s\n", palavra);
        if (modo == 2) registrar_vitoria(nome2);
    }

    printf("Pressione ENTER para sair...\n");
    getchar();

    return 0;
}

void registrar_vitoria(const char nome[]) {
    FILE *f = fopen("ranking.txt", "a");
    if (f) {
        fprintf(f, "%s\n", nome);
        fclose(f);
    }
}

char remove_acento(char c) {
    const char *acentos = "áàãâäÁÀÃÂÄéèêëÉÈÊËíìîïÍÌÎÏóòõôöÓÒÕÔÖúùûüÚÙÛÜçÇ";
    const char *sem_acentos = "aaaaaAAAAAeeeeEEEEiiiiIIIIoooooOOOOOuuuuUUUUcC";
    char *p = strchr(acentos, c);
    if (p) {
        return sem_acentos[p - acentos];
    }
    return c;
}

void normalizar(char s[]) {
    int j = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] != ' ') {
            s[j++] = toupper((unsigned char)remove_acento(s[i]));
        }
    }
    s[j] = '\0';
}

char* escolher_palavra_aleatoria(const char *arquivo_tema) {
    static char palavra[100];
    FILE *f = fopen(arquivo_tema, "r");
    if (!f) {
        printf("Erro ao abrir o arquivo %s\n", arquivo_tema);
        exit(1);
    }
    char palavras[100][100];
    int total = 0;
    while (fgets(palavras[total], sizeof palavras[0], f)) {
        palavras[total][strcspn(palavras[total], "\n")] = '\0';
        total++;
        if (total >= 100) break; // Evita overflow
    }
    fclose(f);
    if (total == 0) {
        printf("Arquivo %s está vazio!\n", arquivo_tema);
        exit(1);
    }
    strcpy(palavra, palavras[rand() % total]);
    return palavra;
}

void mostrar_feedback(const char tentativa[], const char palavra[]) {
    int tam = (int)strlen(palavra);
    int verde[100] = {0};
    int usada[100] = {0};

    // Marca verdes
    for (int i = 0; i < tam; i++) {
        if (tentativa[i] == palavra[i]) {
            verde[i] = 1;
            usada[i] = 1;
        }
    }

    // Mostra feedback
    for (int i = 0; i < tam; i++) {
        if (verde[i]) {
            printf("\033[1;32m%c\033[0m ", tentativa[i]);
        } else {
            int amarelo = 0;
            for (int j = 0; j < tam; j++) {
                if (!usada[j] && tentativa[i] == palavra[j] && tentativa[j] != palavra[j] && !amarelo) {
                    amarelo = 1;
                    usada[j] = 1;
                }
            }
            if (amarelo) {
                printf("\033[1;33m%c\033[0m ", tentativa[i]);
            } else {
                printf("%c ", tentativa[i]);
            }
        }
    }
    printf("\n");
}





