#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore {
    int elemento;
    struct Arvore *esq, *dir; 
} Arvore;

Arvore *novoNo(int elemento) {
    Arvore *No = (Arvore*)malloc(sizeof(Arvore));
    No->elemento = elemento;
    No->esq = NULL;
    No->dir = NULL;
    return No;
}

Arvore *inserir(Arvore *raiz, int elemento) {
    if (raiz == NULL) {
        return novoNo(elemento);
    }
    if (elemento < raiz->elemento) {
        raiz->esq = inserir(raiz->esq, elemento);
    } else if (elemento > raiz->elemento) {
        raiz->dir = inserir(raiz->dir, elemento);
    }
    return raiz;
}

void imprimir(Arvore *raiz) {
    if (raiz == NULL) {
        return;
    }

    imprimir(raiz->esq);
    printf("%d ", raiz->elemento);
    imprimir(raiz->dir);
}

int main(){
    Arvore *raiz = NULL;
    int valor;
    
    while (scanf("%d", &valor) == 1) {
        raiz = inserir(raiz, valor);
    }
    imprimir(raiz);
    printf("\n");
    return 0;
}