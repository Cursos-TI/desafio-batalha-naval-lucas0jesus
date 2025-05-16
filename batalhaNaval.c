#include <stdio.h>

#define TAMANHO 10
#define AGUA 0
#define NAVIO 3
#define ACERTO 1
#define ERRO 2
#define TAMANHO_NAVIO 3

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para validar se o navio cabe no tabuleiro e não se sobrepõe
int validarNavio(int tabuleiro[TAMANHO][TAMANHO], int x, int y, int horizontal) {
    if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO) {
        return 0; // Fora dos limites
    }
    if (horizontal) {
        if (y + TAMANHO_NAVIO > TAMANHO) {
            return 0; // Navio excede limite horizontal
        }
        for (int j = y; j < y + TAMANHO_NAVIO; j++) {
            if (tabuleiro[x][j] != AGUA) {
                return 0; // Já existe um navio
            }
        }
    } else {
        if (x + TAMANHO_NAVIO > TAMANHO) {
            return 0; // Navio excede limite vertical
        }
        for (int i = x; i < x + TAMANHO_NAVIO; i++) {
            if (tabuleiro[i][y] != AGUA) {
                return 0; // Já existe um navio
            }
        }
    }
    return 1; // Posicionamento válido
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO][TAMANHO], int x, int y, int horizontal) {
    if (horizontal) {
        for (int j = y; j < y + TAMANHO_NAVIO; j++) {
            tabuleiro[x][j] = NAVIO;
        }
    } else {
        for (int i = x; i < x + TAMANHO_NAVIO; i++) {
            tabuleiro[i][y] = NAVIO;
        }
    }
}

// Função para exibir o tabuleiro (mostra acertos e erros, esconde navios não atingidos)
void exibirTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\n  ");
    for (int j = 0; j < TAMANHO; j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == ACERTO) {
                printf("X "); // Acerto
            } else if (tabuleiro[i][j] == ERRO) {
                printf("O "); // Erro
            } else {
                printf("~ "); // Água ou navio não atingido
            }
        }
        printf("\n");
    }
}

// Função para processar um ataque
int processarAtaque(int tabuleiro[TAMANHO][TAMANHO], int x, int y) {
    if (x < 0 || x >= TAMANHO || y < 0 || y >= TAMANHO) {
        printf("Coordenadas inválidas!\n");
        return 0;
    }
    if (tabuleiro[x][y] == NAVIO) {
        tabuleiro[x][y] = ACERTO;
        printf("Acerto!\n");
        return 1;
    } else if (tabuleiro[x][y] == AGUA) {
        tabuleiro[x][y] = ERRO;
        printf("Água!\n");
        return 0;
    } else {
        printf("Já atacado!\n");
        return 0;
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    int x, y;

    // Inicializa o tabuleiro com água
    inicializarTabuleiro(tabuleiro);

    // Entrada para o navio horizontal
    printf("Digite as coordenadas (x y) para o navio horizontal (tamanho 3): ");
    scanf("%d %d", &x, &y);
    if (validarNavio(tabuleiro, x, y, 1)) {
        posicionarNavio(tabuleiro, x, y, 1);
    } else {
        printf("Erro: Posicionamento do navio horizontal inválido!\n");
        return 1;
    }

    // Entrada para o navio vertical
    printf("Digite as coordenadas (x y) para o navio vertical (tamanho 3): ");
    scanf("%d %d", &x, &y);
    if (validarNavio(tabuleiro, x, y, 0)) {
        posicionarNavio(tabuleiro, x, y, 0);
    } else {
        printf("Erro: Posicionamento do navio vertical inválido!\n");
        return 1;
    }

    // Loop principal do jogo
    printf("\nTabuleiro inicial (navios escondidos):\n");
    exibirTabuleiro(tabuleiro);

    while (1) {
        printf("\nDigite as coordenadas (x y) para atacar (ou -1 -1 para sair): ");
        scanf("%d %d", &x, &y);
        if (x == -1 && y == -1) {
            printf("Jogo encerrado!\n");
            break;
        }
        processarAtaque(tabuleiro, x, y);
        printf("Tabuleiro atual:\n");
        exibirTabuleiro(tabuleiro);
    }

    return 0;
}
