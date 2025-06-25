// Descrição: teste do jogo Termo simples
// Requer: inputs do usuário correspondentes às tentativas de adivinhação
// Assegura: apresentação do feedback da tentativa, sendo a palavra reescrita com cores diferentes para cada situação.
//           Caso a letra correspondente esteja na posição correta da palavra, o programa retorna a letra em verde.
//           Caso a letra correspondente esteja na posição errada, mas existe na palavra, o programa retorna a letra
//           em amarelo. Caso a letra correspondente não exista na palavra, o programa retorna a letra em branco.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <termios.h>

// Número de palavras no arquivo "possiveis_palavras_chave.txt"
#define PALAVRA_CHAVE 986

// Número de tentativas máximas antes do usuário perder o jogo
#define TENTATIVAS_MAX 6

// Cores e formas no terminal
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define MAGENTA "\033[35m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define RESET "\033[0m"

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
    return (contador == 5) && (strlen(entrada) == 5);
}

// Apaga linhas no terminal dependendo do parâmetro
void apaga_linha(int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\033[1A");  // Sobe uma linha
        printf("\033[2K");  // Apaga a linha
        printf("\r");       // Volta ao início
    }
}

// Verifica cada letra e retorna seu estado de acordo com a palavra-chave
void turno(char entrada[], char palavra_chave[]) {
    apaga_linha(1);
    for (int i = 0; i < 5; i++) {
        if (acertou(entrada, i, palavra_chave)) {
            printf(BOLD GREEN "%c " RESET, entrada[i]);
        }
        else if (qtde_aparece_letra(entrada, i, palavra_chave) > qtde_apareceu_letra(entrada, i, palavra_chave)) {
            printf(BOLD YELLOW "%c " RESET, entrada[i]);
        }
        else {
            printf(BOLD RED "%c " RESET, entrada[i]);
        }
    }
    printf("     ");
}

// Verifica se a entrada do usuário é igual à uma linha do arquivo das possíveis entradas
bool linha_igual(char entrada[], char linha[]) {
    int contador = 0;
    for (int i = 0; i < 5; i++) {
        if (entrada[i] == linha[i]) {
            contador++;
        }
    }
    return contador == 5;
}

// Verifica se a entrada do usuário existe no arquivo das possiveis entradas
bool palavra_existe(char entrada[], FILE *arquivo_entradas) {
    char linha[7];

    while (fgets(linha, sizeof linha, arquivo_entradas) != NULL) {
        if (linha_igual(entrada, linha)) {
            return true;
        }
    }

    return false;
}

// Função que desativa as entradas do usuário durante mensagens de erro para não dar conflito
void disable_input() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Desativa entrada e eco
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Função que reativa as entradas do usuário após a mensagem de erro
void enable_input() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO); // Reativa entrada e eco
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main() {
    printf(MAGENTA "Selecione o modo de jogo:\n");
    printf("1- Termo aleatório\n2- Termo com amigos\n" RESET);
    printf("> ");

    char entrada[160];
    char palavra_chave[6];
    int modo;

    // repetir a pergunta equanto o modo de jogo não é escolhido
    do {
        fgets(entrada, sizeof entrada, stdin);
        sscanf(entrada, "%d", &modo);

        // modo de jogo no qual o programa escolhe uma palavra aleatória no arquivo das possíveis palavras chaves
        if (modo == 1) {
            // arquivo de palavras-chave
            FILE *arquivo_saidas = fopen("possiveis_palavras_chave.txt", "r");

            if (arquivo_saidas == NULL) {
                perror(RED "Impossível abrir arquivo" RESET);
                return 1;
            }

            // aleatorieade de acordo com a hora
            srand(time(NULL));

            // pular para a linha aleatória
            fseek(arquivo_saidas, (rand() % PALAVRA_CHAVE) * 6, SEEK_SET);

            // leia a linha aleatória
            fgets(palavra_chave, sizeof palavra_chave, arquivo_saidas);

            fclose(arquivo_saidas);
        }
        // modo de jogo no qual o usuário seleciona a palavra-chave para que outro usuário adivinhe
        else if (modo == 2) {
            do {
                printf(MAGENTA "Digite a palavra para seu amigo adivinhar: " RESET);
                fgets(entrada, sizeof entrada, stdin);
                entrada[strlen(entrada) - 1] = '\0';  // substitui o '\n' por um '\0'
                
                if (strlen(entrada) > 5) {
                    printf(RED "Erro: palavra muito longa!\n" RESET);
                    disable_input();
                    sleep(2);
                    enable_input();
                    apaga_linha(2);
                }
                else if (strlen(entrada) < 5) {
                    printf(RED "Erro: palavra muito curta!\n" RESET);
                    disable_input();
                    sleep(2);
                    enable_input();
                    apaga_linha(2);
                }
                else {
                    disable_input();
                    // copia a entrada do usuário para a palavra chave
                    for(int i = 0; i < 5; i++) {
                        palavra_chave[i] = entrada[i];
                    }
                    sleep(1);
                    enable_input();
                    apaga_linha(1);
                }
            } while (strlen(entrada) != 5);
        }
        // caso outra entrada que não '1' ou '2'
        else {
            disable_input();
            printf(RED "Erro: digite apenas '1' ou '2' para escolher o modo de jogo\n" RESET);
            sleep(2);

            apaga_linha(2);
            printf("> ");

            enable_input();
        }
    }
    while (modo != 1 && modo != 2);

    FILE *arquivo_entradas = fopen("possiveis_entradas_usuario.txt", "r");

    if (arquivo_entradas == NULL) {
        perror(RED "Impossível abrir arquivo" RESET);
        return 1;
    }

    printf("\n");
    printf("Digite uma palavra:\n");

    int tentativas = 0;
    do {
        fgets(entrada, sizeof entrada, stdin);
        entrada[strlen(entrada) - 1] = '\0';  // substitui o '\n' por um '\0'
        if (strlen(entrada) == 5 && ( palavra_existe(entrada, arquivo_entradas) || modo == 2 )) {
            turno(entrada, palavra_chave);
            tentativas++;
            if (!venceu(entrada, palavra_chave)) {
                printf("Tentativas restantes: %d\n", TENTATIVAS_MAX - tentativas);
            }
            // reposicionar o ponteiro para ler a primeira linha do arquivo novamente
            rewind(arquivo_entradas);
        }
        else {
            disable_input();
            printf(RED "Palavra inválida!\n" RESET);

            sleep(1);

            apaga_linha(2);

            enable_input();
            
            // reposicionar o ponteiro para ler a primeira linha do arquivo novamente
            rewind(arquivo_entradas);
        }
    }
    while (venceu(entrada, palavra_chave) == false && tentativas != TENTATIVAS_MAX);

    fclose(arquivo_entradas);

    if (venceu(entrada, palavra_chave) == true) {
        printf(ITALIC MAGENTA "\nParabéns!!! Você acertou!!!\n" RESET);
    }
    else {
        printf(ITALIC MAGENTA "\nQue pena, você perdeu!\nA palavra era %s\n\n", palavra_chave);
    }

    return 0;
}