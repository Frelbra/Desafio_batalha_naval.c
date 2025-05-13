#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define TAM_HAB 5

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = AGUA;
}

// Exibe o tabuleiro completo
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Exibe coordenadas das partes de um navio
void exibirCoordenadasNavio(int linha, int coluna, char direcao) {
    printf("Coordenadas do navio (%c):\n", direcao);
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : 0);
        int c = coluna + (direcao == 'H' ? i : 0);
        printf("(%d, %d)\n", l, c);
    }
    printf("\n");
}

// Verifica se o navio pode ser posicionado
int podePosicionar(int tab[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : (direcao == 'D' ? i : 0));
        int c = coluna + (direcao == 'H' ? i : (direcao == 'D' ? i : 0));
        if (l >= TAM || c >= TAM || tab[l][c] == NAVIO)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tab[TAM][TAM], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + (direcao == 'V' ? i : (direcao == 'D' ? i : 0));
        int c = coluna + (direcao == 'H' ? i : (direcao == 'D' ? i : 0));
        tab[l][c] = NAVIO;
    }
    exibirCoordenadasNavio(linha, coluna, direcao);
}

// Imprime uma matriz de habilidade 5x5
void exibirHabilidade(int matriz[TAM_HAB][TAM_HAB], const char* nome) {
    printf("Habilidade: %s\n", nome);
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Define a habilidade em formato de cone (para baixo)
void habilidadeCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            matriz[i][j] = 0;

    for (int i = 0; i <= TAM_HAB / 2; i++)
        for (int j = TAM_HAB / 2 - i; j <= TAM_HAB / 2 + i; j++)
            matriz[i + TAM_HAB / 2][j] = 1;
}

// Define habilidade em cruz
void habilidadeCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            matriz[i][j] = 0;

    for (int i = 0; i < TAM_HAB; i++) {
        matriz[i][TAM_HAB / 2] = 1;
        matriz[TAM_HAB / 2][i] = 1;
    }
}

// Define habilidade em octaedro
void habilidadeOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            matriz[i][j] = 0;

    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        int dist = abs(centro - i);
        for (int j = centro - (centro - dist); j <= centro + (centro - dist); j++)
            matriz[i][j] = 1;
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, 2, 1, 'H');  // Horizontal
    posicionarNavio(tabuleiro, 5, 4, 'V');  // Vertical
    exibirTabuleiro(tabuleiro);

    if (podePosicionar(tabuleiro, 0, 6, 'D'))
        posicionarNavio(tabuleiro, 0, 6, 'D'); // Diagonal
    if (podePosicionar(tabuleiro, 7, 2, 'D'))
        posicionarNavio(tabuleiro, 7, 2, 'D'); // Diagonal

    exibirTabuleiro(tabuleiro);

    return 0;
}