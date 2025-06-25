// Descrição: teste do jogo Termo simples
// Requer: inputs do usuário correspondentes às tentativas de adivinhação
// Assegura: apresentação do feedback da tentativa, sendo a palavra reescrita com cores diferentes para cada situação.
//           Caso a letra correspondente esteja na posição correta da palavra, o programa retorna a letra em verde.
//           Caso a letra correspondente esteja na posição errada, mas existe na palavra, o programa retorna a letra
//           em amarelo. Caso a letra correspondente não exista na palavra, o programa retorna a letra em branco.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

// Número de palavras no arquivo "possiveis_palavras_chave.txt"
#define PALAVRA_CHAVE 986

// Verifica se a letra na posição de parâmetro corresponde com a letra na posição da palavra-chave
bool acertou(char entrada[], int posicao, char palavra_chave[]) {
    return (entrada[posicao] == palavra_chave[posicao]);
}

// Verifica a quantidade de vezes que a letra específica aparece na palavra > fora de posição <
int qtde_aparece_letra(char entrada[], int posicao, char palavra_chave[]) {
    int qtde_aparece = 0;
    for (int i = 0; i < 5; i++) {
        if (entrada[posicao] == palavra_chave[i] && !acertou(entrada, i, palavra_chave)) {
                qtde_aparece++;
        }
    }
    return qtde_aparece;
}

// Verifica a quantidade de vezes que a letra específica já apareceu até o momento na palavra
int qtde_apareceu_letra(char entrada[], int posicao, char palavra_chave[]) {
    int qtde_apareceu = 0;
    for (int i = 0; i < posicao; i++) {
        if (entrada[posicao] == entrada[i] && !acertou(entrada, i, palavra_chave)) {
            qtde_apareceu++;
        }
    }
    return qtde_apareceu;
}

// Verifica se o usuáŕio acertou as 5 posições
bool venceu(char entrada[], char palavra_chave[]) {
    int contador = 0;
    for (int i = 0; i < 5; i++) {
        if (acertou(entrada, i, palavra_chave)){
            contador++;
        }
    }
    return (contador == 5);
}

// Verifica cada letra e retorna seu estado de acordo com a palavra-chave
void turno(char entrada[], char palavra_chave[]) {
    for (int i = 0; i < 5; i++) {
        if (acertou(entrada, i, palavra_chave)) {
            printf("%c ", entrada[i]);
        }
        else if (qtde_aparece_letra(entrada, i, palavra_chave) > qtde_apareceu_letra(entrada, i, palavra_chave)) {
            printf("~%c ", entrada[i]);
        }
        else {
            printf("!%c  ", entrada[i]);
        }
    }
    printf("\n");
}

bool linha_igual(char entrada[], char linha[]) {
    int contador = 0;
    for (int i = 0; i < 5; i++) {
        if (entrada[i] == linha[i]) {
            contador++;
        }
    }
    return contador == 5;
}

bool palavra_existe(char entrada[], FILE *arquivo_entradas) {
    char linha[7];

    while (fgets(linha, sizeof linha, arquivo_entradas) != NULL) {
        if (linha_igual(entrada, linha)) {
            return true;
        }
    }

    return false;
}

// Move para linha anterior e apaga
void apaga_linha() {
    printf("\033[1A");  // Sobe uma linha
    printf("\033[2K");  // Apaga a linha
    printf("\r");       // Volta ao início
}

int main() {
    printf("Selecione o modo de jogo:\n");
    printf("1- Termo aleatório\n2- Termo com amigos\n");
    printf("> ");

    char entrada[7];
    char palavra_chave[6];
    int modo;

    // repetir a pergunta equanto o modo de jogo não é escolhido
    do {
        fgets(entrada, sizeof entrada, stdin);
        sscanf(entrada, "%d", &modo);

        if (modo == 1) {
            // arquivo de palavras-chave
            FILE *arquivo_saidas = fopen("possiveis_palavras_chave.txt", "r");

            if (arquivo_saidas == NULL) {
                perror("Impossível abrir arquivo");
                return 1;
            }

            // aleatorieade de acordo com a hora
            srand(time(NULL));

            // pular para uma linha aleatória 
            fseek(arquivo_saidas, (rand() % PALAVRA_CHAVE) * 6, SEEK_SET);

            // leia a linha
            fgets(palavra_chave, sizeof palavra_chave, arquivo_saidas);

            fclose(arquivo_saidas);
        }
        else if (modo == 2) {
            printf("Digite a palavra para seu amigo adivinhar: ");
            fgets(entrada, sizeof entrada, stdin);
            
            // atribui a entrada do usuário como sendo a palavra chave
            for(int i = 0; i < 5; i++) {
                palavra_chave[i] = entrada[i];
            }

            sleep(1);
            apaga_linha();
        }
        else {
            printf("Erro: digite 1 ou 2 para escolher o modo de jogo\n");
            sleep(2);
            for (int i = 0; i < 2; i++) {
                apaga_linha();
            }
            printf("> ");
        }
    }
    while (modo != 1 && modo != 2);

    FILE *arquivo_entradas = fopen("possiveis_entradas_usuario.txt", "r");

    if (arquivo_entradas == NULL) {
        perror("Impossível abrir arquivo");
        return 1;
    }

    do {
        fgets(entrada, sizeof entrada, stdin);
        if (palavra_existe(entrada, arquivo_entradas) || modo == 2) {
            turno(entrada, palavra_chave);
            venceu(entrada, palavra_chave);
            rewind(arquivo_entradas);
        }
        else {
            printf("Palavra inválida!\n");

            sleep(1);

            // apaga as últimas duas mensagens
            for (int i = 0; i < 2; i++) {
                apaga_linha();
            }

            rewind(arquivo_entradas);
        }
    }
    while (venceu(entrada, palavra_chave) == 0);

    fclose(arquivo_entradas);

    printf("Parabéns!!! Você acertou!!!\n");

    return 0;
}