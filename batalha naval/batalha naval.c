#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 10
const char AGUA = '~';
const char NAVIO_JOGADOR = 'J';
const char NAVIO_CPU = 'C';
const char TIRO_AGUA = 'o';
const char TIRO_NAVIO = 'X';

void imprimirCelula(char c) {
    if (c == NAVIO_JOGADOR || c == NAVIO_CPU)
        printf("[~]"); // Esconde navios
    else
        printf("[%c]", c);
}

void imprimirTabuleiro(char tabuleiro[TAMANHO][TAMANHO]) {
    printf("   ");
    for (int j = 0; j < TAMANHO; j++) printf("%2d ", j);
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            imprimirCelula(tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarNavio(char tabuleiro[TAMANHO][TAMANHO], char navio, int *x, int *y) {
    do {
        *x = rand() % TAMANHO;
        *y = rand() % TAMANHO;
    } while (tabuleiro[*x][*y] != AGUA);
    tabuleiro[*x][*y] = navio;
}

int main() {
    char tabuleiro[TAMANHO][TAMANHO];
    int xJog, yJog, xCPU, yCPU;
    int acertouJogador = 0, acertouCPU = 0;
    int tentativasJogador = 0, tentativasCPU = 0;

    srand(time(NULL));

    // Inicializa tabuleiro
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;

    // Posiciona navios
    posicionarNavio(tabuleiro, NAVIO_JOGADOR, &xJog, &yJog);
    posicionarNavio(tabuleiro, NAVIO_CPU, &xCPU, &yCPU);

    printf("Bem-vindo ao Batalha Naval (tabuleiro único)!\n");

    while (!acertouJogador && !acertouCPU) {
        // Turno do jogador
        imprimirTabuleiro(tabuleiro);
        int x, y;
        printf("\nSua vez!\n");
        printf("Digite a linha (0-%d): ", TAMANHO-1);
        scanf("%d", &x);
        printf("Digite a coluna (0-%d): ", TAMANHO-1);
        scanf("%d", &y);

        if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO) {
            printf("Coordenada inválida!\n");
        } else if (tabuleiro[x][y] == TIRO_AGUA || tabuleiro[x][y] == TIRO_NAVIO) {
            printf("Você já atirou aqui!\n");
        } else {
            tentativasJogador++;
            if (tabuleiro[x][y] == NAVIO_CPU) {
                printf("Você acertou o navio da CPU!\n");
                tabuleiro[x][y] = TIRO_NAVIO;
                acertouJogador = 1;
            } else if (tabuleiro[x][y] == NAVIO_JOGADOR) {
                printf("Você acertou seu próprio navio! (não vale ponto)\n");
                tabuleiro[x][y] = TIRO_NAVIO;
            } else {
                printf("Água!\n");
                tabuleiro[x][y] = TIRO_AGUA;
            }
        }

        if (acertouJogador) break;

        // Turno da CPU
        printf("\nVez da CPU...\n");
        int cx, cy;
        do {
            cx = rand() % TAMANHO;
            cy = rand() % TAMANHO;
        } while (tabuleiro[cx][cy] == TIRO_AGUA || tabuleiro[cx][cy] == TIRO_NAVIO);

        tentativasCPU++;
        printf("CPU atirou em (%d, %d)\n", cx, cy);
        if (tabuleiro[cx][cy] == NAVIO_JOGADOR) {
            printf("A CPU acertou seu navio!\n");
            tabuleiro[cx][cy] = TIRO_NAVIO;
            acertouCPU = 1;
        } else if (tabuleiro[cx][cy] == NAVIO_CPU) {
            printf("A CPU acertou o próprio navio! (não vale ponto)\n");
            tabuleiro[cx][cy] = TIRO_NAVIO;
        } else {
            printf("CPU acertou água.\n");
            tabuleiro[cx][cy] = TIRO_AGUA;
        }
    }

    printf("\nTabuleiro final:\n");
    // Mostra navios revelados
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            if (tabuleiro[i][j] == NAVIO_JOGADOR || tabuleiro[i][j] == NAVIO_CPU)
                tabuleiro[i][j] = '*';
    imprimirTabuleiro(tabuleiro);

    if (acertouJogador)
        printf("\nParabéns! Você venceu em %d tentativas.\n", tentativasJogador);
    else
        printf("\nA CPU venceu em %d tentativas.\n", tentativasCPU);

    return 0;
}