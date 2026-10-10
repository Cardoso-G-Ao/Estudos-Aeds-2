#include <stdio.h>
#include <stdlib.h>

// Entrada esperada (mesmo formato da fila):
//   1ª linha: números separados por espaço, terminando com uma letra (ex.: 10 20 30 x)
//   2ª linha: o valor que será empilhado (ex.: 40)

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

// Empilhar: a nova célula entra no TOPO e aponta para o antigo topo
void empilhar(Celula **topo){
    int x;
    if(scanf("%d",&x) != 1){   // não conseguiu ler o valor
        printf("erro\n");
        return;
    }
    Celula *nova = novaCelula(x);
    nova->prox = (*topo);      // a nova célula aponta para quem estava no topo
    (*topo) = nova;            // o topo passa a ser a nova célula
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


    empilhar(&topo);

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