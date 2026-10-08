#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct FilaCircular {
    int vet[MAX + 1];
    int primeiro, ultimo;
} FilaCircular;

void inicializar(FilaCircular *f) {
    f->primeiro = 0;
    f->ultimo = 0;
}

void inserir(FilaCircular *f, int x) {
    if (((f->ultimo + 1) % (MAX + 1)) == f->primeiro) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    f->vet[f->ultimo] = x;
    f->ultimo = (f->ultimo + 1) % (MAX + 1);
}

int remover(FilaCircular *f) {
    
    if (f->primeiro == f->ultimo) {
        printf("Erro: Fila vazia!\n");
        return -1; 
    }
    int resp = f->vet[f->primeiro];
    f->primeiro = (f->primeiro + 1) % (MAX + 1);
    return resp;
}

void mostrar(FilaCircular *f) {
    int i = f->primeiro;
    printf("[ ");
    while (i != f->ultimo) {
        printf("%d ", f->vet[i]);
        i = (i + 1) % (MAX + 1);
    }
    printf("]\n");
}

int main() {
    FilaCircular fila;
    inicializar(&fila);

    inserir(&fila, 10);
    inserir(&fila, 20);
    inserir(&fila, 30);

    printf("Fila atual: ");
    mostrar(&fila);

    int removido = remover(&fila);
    printf("Elemento removido: %d\n", removido);

    printf("Fila apos remocao: ");
    mostrar(&fila);

    return 0;
}