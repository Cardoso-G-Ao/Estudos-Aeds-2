#include <stdio.h>
#include <stdlib.h>

typedef struct Celula {
    int elemento;
    struct Celula *esq, *dir, *sup, *inf;
} Celula;

Celula *novaCelula(int elemento) {
    Celula *No = (Celula*)malloc(sizeof(Celula));
    No->elemento = elemento;
    No->esq = NULL;
    No->dir = NULL;
    No->sup = NULL;
    No->inf = NULL;
    return No;
}

Celula *criarMatriz(int linhas, int colunas) {
    if (linhas <= 0 || colunas <= 0) return NULL;

    Celula *inicio = novaCelula(0);
    Celula *atual = inicio;

    for (int j = 1; j < colunas; j++) {
        atual->dir = novaCelula(0);
        atual->dir->esq = atual;
        atual = atual->dir;
    }

    Celula *linhaAcima = inicio;
    for (int i = 1; i < linhas; i++) {
        Celula *novaLinha = novaCelula(0);
        novaLinha->sup = linhaAcima;
        linhaAcima->inf = novaLinha;

        Celula *celAcima = linhaAcima->dir;
        Celula *celAtual = novaLinha;

        for (int j = 1; j < colunas; j++) {
            Celula *nova = novaCelula(0);
            celAtual->dir = nova;
            nova->esq = celAtual;
            nova->sup = celAcima;
            celAcima->inf = nova;

            celAtual = nova;
            celAcima = celAcima->dir;
        }
        linhaAcima = novaLinha;
    }
    return inicio;
}

void inserir(Celula *inicio, int linha, int coluna, int elemento) {
    Celula *atual = inicio;
    for (int i = 0; i < linha; i++) atual = atual->inf;
    for (int j = 0; j < coluna; j++) atual = atual->dir;
    atual->elemento = elemento;
}

void imprimir(Celula *inicio) {
    if (inicio == NULL) return;
    
    Celula *linhaAtual = inicio;
    while (linhaAtual != NULL) {
        Celula *atual = linhaAtual;
        while (atual != NULL) {
            printf("%d ", atual->elemento);
            atual = atual->dir;
        }
        printf("\n");
        linhaAtual = linhaAtual->inf;
    }
}

int main() {
    int linhas, colunas, valor;
    
    // Leitura das dimensões da matriz (ex: 3 3)
    if (scanf("%d %d", &linhas, &colunas) != 2) {
        return 0;
    }
    
    Celula *matriz = criarMatriz(linhas, colunas);
    
    // Preenchendo a matriz com os valores lidos
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (scanf("%d", &valor) == 1) {
                inserir(matriz, i, j, valor);
            }
        }
    }
    
    imprimir(matriz);
    return 0;
}