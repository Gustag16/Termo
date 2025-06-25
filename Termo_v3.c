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

// Verifica a quantidade de vezes que a letra específica já apareceu até o momento na palavra > fora de posição <
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
            FILE *arquivo = fopen("possiveis_palavras_chave.txt", "r");

            // aleatorieade de acordo com a hora
            srand(time(NULL));

            // pular para uma linha aleatória 
            fseek(arquivo, rand() % PALAVRA_CHAVE * 6, SEEK_SET);

            // retorne a linha
            fgets(palavra_chave, sizeof palavra_chave, arquivo);

            if (arquivo == NULL) {
                perror("Impossível abrir arquivo");
                return 1;
            }

            fclose(arquivo);
        }
        else if (modo == 2) {
            printf("Digite a palavra para seu amigo adivinhar: ");
            fgets(entrada, sizeof entrada, stdin);
            
            // atribui a entrada do usuário como sendo a palavra chave
            for(int i = 0; i < 5; i++) {
                palavra_chave[i] = entrada[i];
            }

            sleep(2);

            // Move para linha anterior e apaga
            printf("\033[1A");  // Sobe uma linha
            printf("\033[2K");  // Apaga a linha
            printf("\r");       // Volta ao início
        }
        else {
            printf("Erro: digite 1 ou 2 para escolher o modo de jogo\n");
        }
    }
    while (modo != 1 && modo != 2);

    do {
        fgets(entrada, sizeof entrada, stdin);
        turno(entrada, palavra_chave);
        venceu(entrada, palavra_chave);
    }
    while (venceu(entrada, palavra_chave) == 0);

    printf("Parabéns!!! Você acertou!!!\n");

    return 0;
}