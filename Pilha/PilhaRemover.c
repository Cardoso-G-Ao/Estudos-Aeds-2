#include <stdio.h>
#include <stdlib.h>

// Entrada esperada (mesmo formato da fila):
//   uma linha com números separados por espaço, terminando com uma letra (ex.: 10 20 30 x)

typedef struct Celula
{
    int elemento;
    struct Celula *prox;
} Celula;

Celula *novaCelula(int elemento)
{
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->elemento = elemento;
    nova->prox = NULL;
    return nova;
}

// Desempilhar: remove a célula do TOPO (o último que entrou)
void desempilhar(Celula **topo){
    if((*topo) == NULL){       // pilha vazia: não há o que remover
        printf("erro\n");
        return;
    }
    Celula *tmp = (*topo);     // guarda a célula que vai sair
    (*topo) = (*topo)->prox;   // o topo passa a ser a célula de baixo
    printf("Desempilhado: %d\n", tmp->elemento);
    tmp->prox = NULL;
    free(tmp);
    tmp = NULL;
}


int main(){
    int valor;
    Celula *topo = NULL;       // a pilha só precisa guardar o topo
    while(scanf("%d",&valor) == 1){
        Celula *nova = novaCelula(valor);
        nova->prox = topo;     // empilha cada número lido
        topo = nova;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);   // descarta o resto da linha


    desempilhar(&topo);


    Celula *atual = topo;      // mostra do topo até a base
    while (atual != NULL) {
        printf("%d ", atual->elemento);
        atual = atual->prox;
    }
    printf("\n");

    atual = topo;              // libera toda a memória
    while (atual != NULL) {
        Celula *proxima = atual->prox;
        free(atual);
        atual = proxima;
    }

    return 0;
}