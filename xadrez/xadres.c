#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define tam 8 // defenindo o tamanho do tabuleiro
char tabuleiro[tam][tam] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'},
    {'R','N','B','Q','K','B','N','R'}

}; // tabuleiro inicial
// Imprime o tabuleiro de xadrez com coordenadas
void print_tabuleiro() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < tam; i++) {
        printf("%d ", tam - i);
        for (int j = 0; j < tam; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Declarações antecipadas
int get_piece_color(char peca);
int get_piece_type(char peca);
int isvalidmove(int fromrow, int fromcol, int torow, int tocol);

// Move uma peça do tabuleiro, validando entrada e regras
void mover_peca(char origem[3], char destino[3]) {
    if (strlen(origem) != 2 || strlen(destino) != 2) {
        printf("Posicao invalida! Use o formato 'e2' ou 'd4'.\n");
        return;
    }
    int x1 = tam - (origem[1] - '0');
    int y1 = origem[0] - 'a';
    int x2 = tam - (destino[1] - '0');
    int y2 = destino[0] - 'a';

    if (x1 < 0 || x1 >= tam || y1 < 0 || y1 >= tam || x2 < 0 || x2 >= tam || y2 < 0 || y2 >= tam) {
        printf("Movimento invalido! As coordenadas devem estar entre a1 e h8.\n");
        return;
    }

    char peca = tabuleiro[x1][y1];
    if (peca == ' ') {
        printf("Nao ha peca na posicao de origem!\n");
        return;
    }
    if (!isvalidmove(x1, y1, x2, y2)) {
        printf("Movimento da peça invalido!\n");
        return;
    }
    if (tabuleiro[x2][y2] != ' ' && get_piece_color(tabuleiro[x2][y2]) == get_piece_color(peca)) {
        printf("Não pode capturar peça da mesma cor!\n");
        return;
    }
    tabuleiro[x2][y2] = peca;
    tabuleiro[x1][y1] = ' ';
}
// Move uma peça preta aleatória do CPU
void cpumover() {
    int fromrow, fromcol, torow, tocol;
    char peca;
    while (1) {
        fromrow = rand() % tam;
        fromcol = rand() % tam;
        torow = rand() % tam;
        tocol = rand() % tam;
        if (tabuleiro[fromrow][fromcol] != ' ' && tabuleiro[fromrow][fromcol] >= 'a' && tabuleiro[fromrow][fromcol] <= 'z') {
            peca = tabuleiro[fromrow][fromcol];
            if (isvalidmove(fromrow, fromcol, torow, tocol)) {
                tabuleiro[torow][tocol] = peca;
                tabuleiro[fromrow][fromcol] = ' ';
                printf("CPU moveu %c de %c%d para %c%d\n",
                    peca,
                    'a' + fromcol, tam - fromrow,
                    'a' + tocol, tam - torow
                );
                fflush(stdout);
                break;
            }
        }
    }
}
int isvalidpawmove(int fromrow, int fromcol, int torow, int tocol) {
    if (fromcol == tocol && (torow == fromrow - 1 || torow == fromrow + 1)) {
        return 1; // movimento valido para peao
    }
    return 0; // movimento invalido
} // funcao que verifica se o movimento do peao e valido
int isvalidrookmove(int fromrow, int fromcol, int torow, int tocol) {
    if (fromrow == torow || fromcol == tocol) {
        return 1; // movimento valido para torre
    }
    return 0; // movimento invalido
} // funcao que verifica se o movimento da torre e valido
int isvalidknightmove(int fromrow, int fromcol, int torow, int tocol) {
    if ((abs(fromrow - torow) == 2 && abs(fromcol - tocol) == 1) || (abs(fromrow - torow) == 1 && abs(fromcol - tocol) == 2)) {
        return 1; // movimento valido para cavalo
    }
    return 0; // movimento invalido
} // funcao que verifica se o movimento do cavalo e valido
int isvalidbishopmove(int fromrow, int fromcol, int torow, int tocol) {
    if (abs(fromrow - torow) == abs(fromcol - tocol)) {
        return 1; // movimento valido para bispo
    }
    return 0; // movimento invalido
} // funcao que verifica se o movimento do bispo e valido
int isvalidqueenmove(int fromrow, int fromcol, int torow, int tocol) {
    if (fromrow == torow || fromcol == tocol || abs(fromrow - torow) == abs(fromcol - tocol)) {
        return 1; // movimento valido para rainha
    }
    return 0; // movimento invalido
} // funcao que verifica se o movimento da rainha e valido
int isvalidkingmove(int fromrow, int fromcol, int torow, int tocol) {
    if (abs(fromrow - torow) <= 1 && abs(fromcol - tocol) <= 1) {
        return 1; // movimento valido para rei
    }
    return 0; // movimento invalido
} // funcao que verifica se o movimento do rei e valido

void cpusmartmove(int turn) { 
    int fromrow, fromcol, torow, tocol;
    char peca;
    for (fromrow = 0; fromrow < tam; fromrow++) {
        for (fromcol = 0; fromcol < tam; fromcol++) {
            peca = tabuleiro[fromrow][fromcol];
            if (peca != ' ' && (turn % 2 == 0) == (peca >= 'a' && peca <= 'z')) {
                // tenta mover a peca
                for (torow = 0; torow < tam; torow++) {
                    for (tocol = 0; tocol < tam; tocol++) {
                        if (isvalidmove(fromrow, fromcol, torow, tocol)) {
                            tabuleiro[torow][tocol] = peca;
                            tabuleiro[fromrow][fromcol] = ' ';
                            return;
                        }
                    }
                }
            }
        }
    }
}
int get_piece_type(char peca) {
    if (peca == 'p' || peca == 'P') return 1; // peao
    if (peca == 'r' || peca == 'R') return 2; // torre
    if (peca == 'n' || peca == 'N') return 3; // cavalo
    if (peca == 'b' || peca == 'B') return 4; // bispo
    if (peca == 'q' || peca == 'Q') return 5; // rainha
    if (peca == 'k' || peca == 'K') return 6; // rei
    return 0; // tipo de peca desconhecido
} // funcao que retorna o tipo de peca
int get_piece_color(char peca) {
    if (peca >= 'a' && peca <= 'z') return 1; // preto
    if (peca >= 'A' && peca <= 'Z') return 2; // branco
    return 0; // cor de peca desconhecida
} // funcao que retorna a cor da peca
int isvalidmove(int fromrow, int fromcol, int torow, int tocol) {
    char peca = tabuleiro[fromrow][fromcol];
    if (peca == ' ') return 0; // posicao de origem vazia

    int piece_type = get_piece_type(peca);
    int piece_color = get_piece_color(peca);

    // Verifica se a posicao de destino esta ocupada por uma peca da mesma cor
    if (tabuleiro[torow][tocol] != ' ' && get_piece_color(tabuleiro[torow][tocol]) == piece_color) {
        return 0; // movimento invalido
    }

    switch (piece_type) {
        case 1: return isvalidpawmove(fromrow, fromcol, torow, tocol); // peao
        case 2: return isvalidrookmove(fromrow, fromcol, torow, tocol); // torre
        case 3: return isvalidknightmove(fromrow, fromcol, torow, tocol); // cavalo
        case 4: return isvalidbishopmove(fromrow, fromcol, torow, tocol); // bispo
        case 5: return isvalidqueenmove(fromrow, fromcol, torow, tocol); // rainha
        case 6: return isvalidkingmove(fromrow, fromcol, torow, tocol); // rei
        default: return 0; // tipo de peca desconhecido
    }
} // funcao que verifica se o movimento e valido
int getpiecevalue(char peca) {
    switch (peca) {
        case 'p': return 1; // peao
        case 'r': return 5; // torre
        case 'n': return 3; // cavalo
        case 'b': return 3; // bispo
        case 'q': return 9; // rainha
        case 'k': return 0; // rei (sem valor)
        default: return 0; // peca desconhecida
    }
} // funcao que retorna o valor da peca
void cpuevaluatemove(int fromrow, int fromcol, int torow, int tocol) {
    char peca = tabuleiro[fromrow][fromcol];
    if (isvalidmove(fromrow, fromcol, torow, tocol)) {
        int piece_value = getpiecevalue(peca);
        // Avalia o movimento com base no valor da peça
        printf("Movimento avaliado: %d\n", piece_value);
    }
}
// Limpa o buffer do teclado após scanf
void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    char origem[3], destino[3];
    int turn = 0;
    while (1) {
        print_tabuleiro();
        if (turn % 2 == 0) {
            printf("Turno do jogador\n");
            printf("Digite a posicao de origem (ex: e2): ");
            scanf("%s", origem);
            limpaBuffer();
            printf("Digite a posicao de destino (ex: e4): ");
            scanf("%s", destino);
            limpaBuffer();
            mover_peca(origem, destino);
        } else {
            printf("Turno do CPU\n");
            cpumover();
            fflush(stdout); // força a impressão do movimento do CPU antes do tabuleiro
            print_tabuleiro(); // Mostra o tabuleiro após o movimento do CPU
            // Se quiser usar cpusmartmove, substitua a linha acima por:
            // cpusmartmove(turn);
        }
        turn++;
    }
    return 0;
} // funcao principal