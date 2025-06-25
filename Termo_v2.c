// Descrição: teste do jogo Termo simples
// Requer: inputs do usuário correspondentes às tentativas de adivinhação
// Assegura: apresentação do feedback da tentativa, sendo a palavra reescrita com cores diferentes para cada situação.
//           Caso a letra correspondente esteja na posição correta da palavra, o programa retorna a letra em verde.
//           Caso a letra correspondente esteja na posição errada, mas existe na palavra, o programa retorna a letra
//           em amarelo. Caso a letra correspondente não exista na palavra, o programa retorna a letra em branco.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
            printf(" %c  ", entrada[i]);
            printf("DEBUG: aparece %d, apareceu %d \n", qtde_aparece_letra(entrada, i, palavra_chave),
                qtde_apareceu_letra(entrada, i, palavra_chave));
        }
        else if (qtde_aparece_letra(entrada, i, palavra_chave) > qtde_apareceu_letra(entrada, i, palavra_chave)) {
            printf("~%c  ", entrada[i]);
            printf("DEBUG: aparece %d, apareceu %d \n", qtde_aparece_letra(entrada, i, palavra_chave),
                qtde_apareceu_letra(entrada, i, palavra_chave));
        }
        else {
            printf("!%c  ", entrada[i]);
            printf("DEBUG: aparece %d, apareceu %d \n", qtde_aparece_letra(entrada, i, palavra_chave),
                qtde_apareceu_letra(entrada, i, palavra_chave));
        }
    }
    printf("\n");
}

int main() {
    // Palavra-chave (escolhida aleatoriamente no futuro)
    char palavra_chave[5] = {'J', 'O', 'G', 'O', 'S'};
    char entrada[7];

    do {
        fgets(entrada, sizeof entrada, stdin);
        turno(entrada, palavra_chave);
        venceu(entrada, palavra_chave);
    }
    while (venceu(entrada, palavra_chave) == 0);

    printf("Parabéns!!! Você acertou!!!\n");

    return 0;
}