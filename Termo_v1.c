// Descrição: teste do jogo Termo simples
// Requer: inputs do usuário correspondentes às tentativas de adivinhação
// Assegura: apresentação do feedback da tentativa, sendo a palavra reescrita com cores diferentes para cada situação.
//           Caso a letra correspondente esteja na posição correta da palavra, o programa retorna a letra em verde.
//           Caso a letra correspondente esteja na posição errada, mas existe na palavra, o programa retorna a letra
//           em amarelo. Caso a letra correspondente não exista na palavra, o programa retorna a letra em branco.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Descrição: função que verifica se uma letra no input aparece na palavra-chave fora da posição correta
// Param: entrada[] (palavra digitada pelo usuário), posicao (posicao da letra na palavra), palavra_chave (a palavra
//        que deve ser advinhada)
// Return: retorna um booleano
bool aparece_palavra(char entrada[], int posicao, char palavra_chave[]) {
    bool aparece = 0;
    for (int i = 0; i < 5; i++) {
        if (entrada[posicao] == palavra_chave[i] && posicao != i) {
                aparece = 1;
        }
    }
    return aparece;
}

bool acertou(char entrada[], int posicao, char palavra_chave[]) {
    return (entrada[posicao] == palavra_chave[posicao]);
}

bool venceu(char entrada[], char palavra_chave[]) {
    int contador = 0;
    for (int i = 0; i < 5; i++) {
        if (acertou(entrada, i, palavra_chave)){
            contador++;
        }
    }
    return (contador == 5);
}

void turno(char entrada[], char palavra_chave[]) {
    for (int i = 0; i < 5; i++) {
        if (acertou(entrada, i, palavra_chave)) {
            printf("%c ", entrada[i]);
        }
        else if (aparece_palavra(entrada, i, palavra_chave)) {
            printf("~%c ", entrada[i]);
        }
        else {
            printf("!%c  ", entrada[i]);
        }
    }
    printf("\n");
}

int main() {
    // Palavra-chave (escolhida aleatoriamente no futuro)
    char palavra_chave[5] = {'P', 'A', 'V', 'I', 'O'};
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